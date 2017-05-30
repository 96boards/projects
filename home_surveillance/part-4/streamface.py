# strreamface.py - Stream the detected faces to AWS S3 bucket
# Author - Manivannan Sadhasivam
#
################################################################

# Import libraries
import cv2
import numpy as np
import boto3

# Create boto object
s3 = boto3.resource('s3')

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

face_count = 0
usr_1_instance = 1
usr_2_instance = 1 

# Function to upload image onto S3 bucket
def upload(image):
        data = open(image, 'rb')
        s3.Bucket('homesurveillance').put_object(Key=image, Body=data)
	return

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

                # User 1
                Id="Mani"
		
		# Save the captured frame under captured directory
		image = "captured/" + str(Id) + "_" + str(face_count) + ".jpg"
		cv2.imwrite(image ,frame)

		# Upload the first instance of the detected frame to S3 bucket
		if(usr_1_instance):
			upload(image)
			usr_1_instance = 0
		face_count += 1
	    elif(Id == 2):

                # User 2
		Id = "Bharathi"

		# Save the captured frame under captured directory
                image = "captured/" + str(Id) + "_" + str(face_count) + ".jpg"
                cv2.imwrite(image ,frame)

		# Upload the first instance of the detected frame to S3 bucket
                if(usr_2_instance):
                        upload(image)
			usr_2_instance = 0
                face_count += 1		
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

