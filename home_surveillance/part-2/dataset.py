# dataset.py - Create dataset for face recognition
# Author - Manivannan Sadhasivam
#
################################################################

# Import OpenCV library
import cv2

# Create VideoCapture object for camera id 0
cap = cv2.VideoCapture(0)

# Load classifier
detector=cv2.CascadeClassifier('haarcascade_frontalface_default.xml')

# Prompt for person name
id = raw_input('Enter person ID: ')
count = 0
max_count = 20

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
        cv2.imwrite("dataset/User." + id + '.' + str(count) + ".jpg", gray[y:y+h,x:x+w])

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
