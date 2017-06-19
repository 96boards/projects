# Title: trainer.py - Create trainer model using dataset
# Author: Manivannan Sadhasivam
# Copyright (c) 2017 Linaro Limited
#
################################################################

# Import libraries
import cv2,os
import numpy as np
from PIL import Image

# Create Local Binary Patterns Histograms (LBPH) recognizer
recognizer = cv2.face.createLBPHFaceRecognizer()

# Load the classifier 
detector = cv2.CascadeClassifier("haarcascade_frontalface_default.xml");

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
