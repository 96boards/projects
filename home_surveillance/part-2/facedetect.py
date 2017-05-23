# facedetect.py - Implement face detection using trainned models
# Author - Manivannan Sadhasivam
#
################################################################

# Import libraries
import cv2
import numpy as np

# Create Local Binary Patterns Histograms (LBPH) recognizer
recognizer = cv2.face.createLBPHFaceRecognizer()

# Load the trainner
recognizer.load('trainner/trainner.yml')

# Load the classifier
faceCascade = cv2.CascadeClassifier("haarcascade_frontalface_default.xml");

# Create VideoCapture object for camera id 0
cap = cv2.VideoCapture(0)

fontFace = cv2.FONT_HERSHEY_SIMPLEX
fontScale = 1
fontColor = (255, 255, 255)

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
    faces=faceCascade.detectMultiScale(gray, 1.2,5)

    for(x,y,w,h) in faces:
	
    	# Draw rectangle at the face
        cv2.rectangle(frame,(x,y),(x+w,y+h),(225,0,0),2)

    	# Identify the face
        Id, conf = recognizer.predict(gray[y:y+h,x:x+w])
       
	# Match the ID with person name
	if(conf<50):
            if(Id == 1):
                Id="Mani"
            else:
                Id="Unknown"
        else:
            Id = "Unknown"

	# Print name of the identified face
        cv2.putText(frame,str(Id), (x,y+h), fontFace, fontScale, fontColor)

    # Show the captured frame
    cv2.imshow('frame',frame) 

    if cv2.waitKey(10) & 0xFF==ord('q'):
        break

# Do cleanup
cap.release()
cv2.destroyAllWindows()
