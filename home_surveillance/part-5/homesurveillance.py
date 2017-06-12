# homesurveillance.py - Script to implement facedetection combined with webcam
#			control and streaming of detected faces to AWS cloud. 
#			Live streaming is also added with the help of Flask
#			micro web framework
#
# Author - Manivannan Sadhasivam
#
#################################################################

import threading
import time
import signal
import sys

from flask import Flask, render_template, Response
from stream import facedetect

# Initialize global variables
face_obj = 0
app_run = True
app = Flask(__name__)

# SIGINT handler
def signal_handler(signal, frame):
    print "exiting"
    sys.exit(0)

def run(stream):
    global app_run
    app_run = False
    time.sleep(2) 
    try:
        while True:
            frame = stream.capture()
            yield (b'--frame\r\n'
               b'Content-Type: image/jpeg\r\n\r\n' + frame + b'\r\n\r\n')
    except:
        app_run = True

# Background thread to detect faces and stream
def detect_thread():
    global app_run
    global face_obj
    
    # Create facedetect object
    face_obj = facedetect()
    while True:
        # Stream detected faces
        if app_run:
            face_obj.stream()

# Function to render html page
@app.route('/')
def index():
    return render_template('index.html')

# Function to stream video in html page
@app.route('/video_feed')
def video_feed():
    global face_obj
    return Response(run(face_obj),
                    mimetype='multipart/x-mixed-replace; boundary=frame')

if __name__ == '__main__':
    # Create a thread for running facedetection
    thread = threading.Thread(target=detect_thread)
    thread.daemon = True

    # Start the thread
    thread.start()

    # Attach the SIGNINT handler
    signal.signal(signal.SIGTERM, signal_handler)

    # Start the server
    app.run(host='0.0.0.0', debug=False)
