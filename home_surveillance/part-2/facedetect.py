# Title: facedetect.py - Implement face detection using trainned models
# Author: Manivannan Sadhasivam
# Copyright (c) 2017 Linaro Limited
#
################################################################

# Import libraries
import cv2
import numpy as np
import collections
import os

f = os.popen("ls -lrt /dev/video*") 
for line in f.readlines(): 
    print line
    camNO = int(line[-2])
    print "Camera detected:"

print camNO
# Create Local Binary Patterns Histograms (LBPH) recognizer
recognizer = cv2.face.createLBPHFaceRecognizer()

# Read the file with Id Vs Names CSV
file = open("file.txt","r")
data = file.readlines()

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
# Load the trainer
recognizer.load('trainer/trainer.yml')

# Load the classifier
#faceCascade = cv2.CascadeClassifier("lbpcascade_frontalface.xml");
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
i=0
while True:
    e1 = cv2.getTickCount()
    # Capture the frame
    ret, frame = cap.read()
    if i%11 == 0:
        # Convert from BGR to GRAY color-space
        gray = cv2.cvtColor(frame,cv2.COLOR_BGR2GRAY)

        # Detect objects of different sizes
        faces=faceCascade.detectMultiScale(gray, 1.2,5)

    for(x,y,w,h) in faces:
	
    	# Draw rectangle at the face
        cv2.rectangle(frame,(x,y),(x+w,y+h),(225,0,0),2)

    	# Identify the face
        Id, conf = recognizer.predict(gray[y:y+h,x:x+w])
        #print Id,conf
	
	if(conf<100):
            printName = str(NameList.get(str(Id)))
            printName = printName[:-4]
            printName = printName[2:]
            #print printName
        else:
            printName = "Unknown"

	# Print name of the identified face
        cv2.putText(frame,printName, (x,y+h), fontFace, fontScale, fontColor,font_weight)

    # Show the captured frame
    cv2.imshow('frame',frame) 
    e2 = cv2.getTickCount()
    time = (e2 - e1)/ cv2.getTickFrequency()
    #print time

    if cv2.waitKey(10) & 0xFF==ord('q'):
        break
    i += 1
    
# Do cleanup
cap.release()
cv2.destroyAllWindows()
