# facedetect.py - Implement face detection using trainned models
#                 and also stream the detected faces to AWS cloud
# Author - Manivannan Sadhasivam
#
#################################################################

# Import libraries
import cv2
import numpy as np
import boto3
import serial
import struct

class facedetect(object):
    # Constructor
    def __init__(self):
        # Create boto object
        self.s3 = boto3.resource('s3')

        # Create Local Binary Patterns Histograms (LBPH) recognizer
        self.recognizer = cv2.face.createLBPHFaceRecognizer()

        # Load the trainner
        self.recognizer.load('trainner/trainner.yml')

        # Load the classifier
        self.faceCascade = cv2.CascadeClassifier("haarcascade_frontalface_default.xml");

        # Create VideoCapture object for camera id 0
        self.cap = cv2.VideoCapture(0)

        self.fontFace = cv2.FONT_HERSHEY_SIMPLEX
        self.fontScale = 1
        self.fontColor = (255, 255, 255)

        self.face_count = 0
        self.usr_1_instance = 1
        self.usr_2_instance = 1

        # Print identified name at the center of image
        selfret, frame = self.cap.read()
        self.locy = int(frame.shape[0]/2)
        self.locx = int(frame.shape[1]/2)

        self.ser = serial.Serial('/dev/ttyACM0',9600)

    # Function to upload image onto S3 bucket
    def upload(self,image):
        data = open(image, 'rb')
        self.s3.Bucket('homesurveillance').put_object(Key=image, Body=data)
        return

    def stream(self): 
        # Capture the frame
        ret, frame = self.cap.read()

        # Convert from BGR to GRAY color-space
        gray = cv2.cvtColor(frame,cv2.COLOR_BGR2GRAY)

        # Detect objects of different sizes
        faces = self.faceCascade.detectMultiScale(gray, 1.2,5)

        for(x,y,w,h) in faces:           
            # Draw rectangle at the face
            cv2.rectangle(frame,(x,y),(x+w,y+h),(225,0,0),2)

            # Identify the face
            Id, conf = self.recognizer.predict(gray[y:y+h,x:x+w])
           
            # Match the ID with person name
            if(conf<50):
                if(Id == 1):
                    Id="Mani"
                    
                    # Save the captured frame under captured directory
                    image = "captured/" + str(Id) + "_" + str(self.face_count) + ".jpg"
                    cv2.imwrite(image ,frame)

                    # Upload the first instance of the detected frame to S3 bucket
                    if(self.usr_1_instance):
                            self.upload(image)
                            self.usr_1_instance = 0
                    self.face_count += 1

                    # Send x axis info to arduino as msb followed by lsb
                    lsb = (x) & 0xff
                    msb = ((x) >> 8) & 0xff;
                    self.ser.write(struct.pack('>B', msb))
                    self.ser.write(struct.pack('>B', lsb))

                    # Send y axis info to arduino as msb followed by lsb
                    lsb = (y) & 0xff
                    msb = ((y) >> 8) & 0xff;
                    self.ser.write(struct.pack('>B', msb))
                    self.ser.write(struct.pack('>B', lsb))

                elif(Id == 2):
                    Id = "Bharathi"

                    # Save the captured frame under captured directory
                    image = "captured/" + str(Id) + "_" + str(face_count) + ".jpg"
                    cv2.imwrite(image ,frame)

                    # Upload the first instance of the detected frame to S3 bucket
                    if(self.usr_2_instance):
                            self.upload(image)
                            self.usr_2_instance = 0
                    self.face_count += 1		
                else:
                    Id="Unknown"
            else:
                Id = "Unknown"

            # Print name of the identified face
            cv2.putText(frame,str(Id), (x,y+h), self.fontFace, self.fontScale, self.fontColor)

        # Show the captured frame
        cv2.imshow('frame',frame) 
        ret, jpeg = cv2.imencode('.jpg', frame)
        return jpeg.tobytes()

     # Destructor
    def __del__(self):
        # Do cleanup
        self.cap.release()
        cv2.destroyAllWindows()

