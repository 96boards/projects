# Title: facetrack.py - Track the known face using Webcam mounted using servo
# Author: Manivannan Sadhasivam
# Copyright (c) 2017 Linaro Limited
################################################################

# Import libraries
import cv2
import numpy as np
import serial
import struct
import collections
import os

f = os.popen("ls -lrt /dev/video*") 
for line in f.readlines(): 
    print line
    camNO = int(line[-2])
    print "Camera detected:"

print camNO
Trackname = raw_input('Enter Name of the person you want to track: ')

ser = serial.Serial('/dev/tty96B0',9600)

# Create Local Binary Patterns Histograms (LBPH) recognizer
recognizer = cv2.face.createLBPHFaceRecognizer()

# Read the file with Id Vs Names CSV
file = open("file.txt","r")
data = file.readlines()
print "."
print "."
print "."
print "."
print "."
print "List of authorized users:"
NameList = collections.defaultdict(list)
for line in data:
    words = line.split(",")
    if len(words) > 0:
        tempId = words[0]
        tempName = words[1]
        print tempId,tempName
        NameList[tempId].append(tempName)
file.close

print "."
print "."
print "."
print "."
print "Launching the Video Stream."
# Load the trainner
recognizer.load('trainer/trainer.yml')

# Load the classifier
faceCascade = cv2.CascadeClassifier("haarcascade_frontalface_default.xml");

# Create VideoCapture object for camera id 0
cap = cv2.VideoCapture(camNO)

fontFace = cv2.FONT_HERSHEY_SIMPLEX
fontScale = 1
fontColor = (0, 0, 255)
font_weight = 2
# Print identified name at the center of image
ret, frame = cap.read()
locy = int(frame.shape[0]/2)
locx = int(frame.shape[1]/2)

while True:

    # Capture the frame
    ret, frame = cap.read()
    
    # Convert from BGR to GRAY color-space
    gray = cv2.cvtColor(frame,cv2.COLOR_BGR2GRAY)

    # Detect objects of different sizes
    faces = faceCascade.detectMultiScale(gray, 1.2,5)

    for(x,y,w,h) in faces:
    
    # Draw rectangle at the face
        cv2.rectangle(frame,(x,y),(x+w,y+h),(225,0,0),2)

    # Identify the face
        Id, conf = recognizer.predict(gray[y:y+h,x:x+w])
       
	if(conf<100):
            printName = str(NameList.get(str(Id)))
            printName = printName[:-4]
            printName = printName[2:]
            if(printName==Trackname):

                # Send x axis info to arduino as msb followed by lsb
		lsb = (x) & 0xff
		msb = ((x) >> 8) & 0xff;
		ser.write(struct.pack('>B', msb))
		ser.write(struct.pack('>B', lsb))
                # Send y axis info to arduino as msb followed by lsb
                lsb = (y) & 0xff
                msb = ((y) >> 8) & 0xff;
                ser.write(struct.pack('>B', msb))
                ser.write(struct.pack('>B', lsb))
        else:
            Id="Unknown"

    # Print name of the identified face
        cv2.putText(frame,printName, (x,y+h), fontFace, fontScale, fontColor,font_weight)

    # Show the captured frame
    cv2.imshow('frame',frame) 

    if cv2.waitKey(10) & 0xFF==ord('q'):
        break

# Do cleanup
cap.release()
cv2.destroyAllWindows()
