# Part 3: Webcam tracking using Sensor Mezzanine

Track the known face infront of Webcam using Sensor Mezzanine and Dragonboard410C. Webcam should be
mounted on Pan and Tilt setup with micro servos.

### Hardware requirements and Setup:

* Dragonboard410C
* USB Webcam
* Sensors Mezzanine
* Servo mount - Pan and Tilt
* Micro servos

Assemble Pan and Tilt servo by following the instructions [here](https://learn.adafruit.com/mini-pan-tilt-kit-assembly/getting-started). Then mount USB webcam on servo assembly and connect to Sensors Mezzanine according to the following connections:

* Pin 9   —-> Servo controlling X axis
* Pin 10  —-> Servo controlling Y axis
* 5v      —-> Servo Vcc
* Gnd     —-> Servo Gnd

Finally, connect Sensors Mezzanine , USB webcam and other I/O devices (Monitor, Keyboard) to Dragonboard.

### Software Dependencies:
 
Installed the dependencies mentioned in [Part-2](../part-2) along with the following:

``` shell
$ sudo easy_install pyserial
```
### Arduino Programming

``` shell
$ git clone https://github.com/96boards/projects.git
$ cd projects/home-surveillance/part-3
```
Open facetrack.ino using Arduino IDE and upload the code to Sensor Mezzanine with the following settings:

* Board 	       ----> Arduino Uno
* Serial Port    ----> /dev/tty96B0
* Programmer     ----> AVRISP mkII

### Webcam Tracking

Place the trained dataset and haarcascade_frontalface_default.xml to part-3 directory

```shell
$ cp -r ../part-2/trainer ../part-2/haarcascade_frontalface_default.xml ./
$ sudo python facetrack.py
```

[Link to Blog](http://www.96boards.org/blog/part-3-home-surveillance-project-96boards/)

