# Part 3: Webcam tracking using Sensor Mezzanine

Track the known face infront of Webcam using Sensor Mezzanine and Dragonboard410C. Webcam should be
mounted on Pan and Tilt setup with micro servos.

### Hardware requirements:

* Dragonboard410C
* USB Webcam
* Sensors Mezzanine
* Servo mount - Pan and Tilt
* Micro servos

### Software Dependencies:
 
Installed the dependencies mentioned in [Part-2](../part-2) along with the following:

``` shell
$ sudo apt-get install pyserial
```
### Arduino Programming

Open facetrack.ino using Arduino IDE and upload the code to Sensor Mezzanine with the following settings:

* Board 	       ----> Arduino Uno
* Serial Port    ----> /dev/tty96B0
* Programmer     ----> AVRISP mkII

### Webcam Tracking

``` shell
$ git clone https://github.com/96boards/projects.git
$ cd projects/home-surveillance/part-3
```
Place the trained dataset and haarcascade_frontalface_default.xml to this directory

```shell
$ sudo python facetrack.py
```

[Link to Blog](http://www.96boards.org/blog/part-3-home-surveillance-project-96boards/)

