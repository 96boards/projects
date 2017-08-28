# Title: dataset.py - Create dataset for face recognition
# Author: Manivannan Sadhasivam
# Copyright (c) 2017 Linaro Limited
#
################################################################

# Import OpenCV library
import cv2,os
import numpy as np
from PIL import Image
import os

f = os.popen("ls -lrt /dev/video*") 
for line in f.readlines(): 
    print line
    camNO = int(line[-2])
    print "Camera detected:"

print camNO
# Create VideoCapture object for camera id 0
cap = cv2.VideoCapture(camNO)

# Read / Write from a text file to keep track of ID's and Names.
# File format is CSV
CurrentId = 0
CurrentName = "None"
file = open("file.txt","rw")
data = file.readlines() 
if len(data) > 0:
    for line in data:
        words = line.split(",")
        if len(words) > 0:
            CurrentId = words[0]
            CurrentName = words[1]
        else:
            print ""

file.close

# Load classifier
detector=cv2.CascadeClassifier('haarcascade_frontalface_default.xml')

# Prompt for person name
id = int(CurrentId) + 1
print "Make sure there is only one face in front of the Camera!!!"
print "Adding ID Number"
print id
Newname = raw_input('Enter Name: ')

file = open("file.txt", "a") 
file.write(str(id))
file.write(",")
file.write(Newname)
file.write("\n")
file.close 

print "."
print "."
print "."
print "."
print "Launching the Video Stream."
count = 0

# Maximum count for the dataset
max_count = 30

while(True):

    # Capture and return video frame
    ret, frame = cap.read()

    # Convert from BGR to GRAY color-space
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    # Detect objects of different sizes
    faces = detector.detectMultiScale(gray, 1.3, 5)

    for (x,y,w,h) in faces:

	# Draw rectangle around the face
        cv2.rectangle(frame,(x,y),(x+w,y+h),(255,0,0),2)
        
        # Save the captured face in dataset folder
        cv2.imwrite("dataset/User." + str(id) + '.' + str(count) + ".jpg", gray[y:y+h,x:x+w])

	# Show the captured frame
        cv2.imshow('frame',frame)

	print "Captured frame %d" % count

        # Increment count value
        count += 1

    # Wait for 100 miliseconds 
    if cv2.waitKey(100) & 0xFF == ord('q'):
        break

    # Break if count value exceeds 20
    elif count > max_count:
        break
 
# Do cleanup
cap.release()
cv2.destroyAllWindows()

print "Wait for the program to finish Training..."

# Create Local Binary Patterns Histograms (LBPH) recognizer
recognizer = cv2.face.createLBPHFaceRecognizer()

# Load the classifier 
detector = cv2.CascadeClassifier("lbpcascade_frontalface.xml");

def getImagesAndLabels(path):

    # Get path of all files in the folder
    imagePaths = [os.path.join(path,f) for f in os.listdir(path)] 

    # Create empth face list
    faceSamples = []

    #create empty ID list
    Ids = []

    # Loop through all image paths
    for imagePath in imagePaths:

        # Load the and convert it to PIL image
        pilImage = Image.open(imagePath).convert('L')

        # Convert PIL image into numpy array
        imageNp = np.array(pilImage,'uint8')

        # Get Id from the image
        Id = int(os.path.split(imagePath)[-1].split(".")[1])

        # Extract the face from the training image sample
        faces = detector.detectMultiScale(imageNp)

        # If face is detected, append the face and Id to list
        for (x,y,w,h) in faces:
        
        # Append the face to list
            faceSamples.append(imageNp[y:y+h,x:x+w])

        # Append the Id to list
            Ids.append(Id)

    return faceSamples,Ids

# Get faces and Ids from the dataset folder
faces,Ids = getImagesAndLabels('dataset')

# Train the recognizer for detected faces
recognizer.train(faces, np.array(Ids))

# Save the recognizer out in trainer.yml
recognizer.save('trainer/trainer.yml')
