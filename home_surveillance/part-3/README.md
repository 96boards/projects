# Part 3: Webcam tracking using Sensor Mezzanine

Track the known face infront of Webcam using Sensor Mezzanine and Dragonboard410C. Following are the steps necessary to acheive Webcam tracking.

If you would like to read more about this project, please visit [this blog](http://www.96boards.org/blog/part-3-home-surveillance-project-96boards/) written by Manivannan Sadhasivam.


# Table of Contents

- [1) Hardware](#1-hardware)
   - [1.1) Hardware requirements](#11-hardware-requirements)
   - [1.2) Hardware setup](#12-hardware-setup)
- [2) Software](#2-software)   
   - [2.1) Operating System](#21-operating-system)
   - [2.2) Package dependencies](#22-package-dependencies)
   - [2.3) Arduino Programming](#23-arduino-programming)
- [3) Project Execution](#3-project-execution)

***

# 1) Hardware

## 1.1 Hardware requirements

- [DragonBoard 410c](http://www.96boards.org/product/dragonboard410c/)
- [96Boards Compliant Power Supply](http://www.96boards.org/product/power/)
- USB Webcam
- [Sensors Mezzanine](http://www.96boards.org/product/sensors-mezzanine/)
- [Pan/Tilt Camera Mount with Micro Servos](https://www.arrow.com/en/products/1967/adafruit-industries)

## 1.2 Hardware setup

- DragonBoard 410 is powered off
- Assemble Pan and Tilt servo by following the instructions [here](https://learn.adafruit.com/mini-pan-tilt-kit-            assembly/getting-started)
- Mount USB webcam on servo assembly and connect to Sensors Mezzanine according to the following connections:
  - Pin 9   —-> Servo controlling X axis
  - Pin 10  —-> Servo controlling Y axis
  - 5v      —-> Servo Vcc
  - Gnd     —-> Servo Gnd

- Connect Sensors Mezzanine
- Connect USB webcam 
- Connect I/O devices (Monitor, Keyboard, etc...)
- Power on your DragonBoard 410c with 96Boards compliant power supply

# 2) Software

## 2.1 Operating System

- [Linaro Debian based OS (latest)](https://github.com/96boards/documentation/blob/master/ConsumerEdition/DragonBoard-410c/Downloads/Debian.md)

## 2.2 Package Dependencies
 
Installed the dependencies mentioned in [Part-2](../part-2) along with the following:

``` shell
$ sudo easy_install pyserial
```
## 2.3 Arduino Programming

``` shell
$ git clone https://github.com/96boards/projects.git
$ cd projects/home-surveillance/part-3
```
Open facetrack.ino using Arduino IDE and upload the code to Sensor Mezzanine with the following settings:

* Board 	       ----> Arduino Uno
* Serial Port    ----> /dev/tty96B0
* Programmer     ----> AVRISP mkII

# 3) Project Execution

Place the trained dataset and haarcascade_frontalface_default.xml to part-3 directory. Also, update the USB webcam video source as specified in [Part-2](../part-2/README.md#31-creating-dataset)

```shell
$ cp -r ../part-2/trainer ../part-2/haarcascade_frontalface_default.xml ./
$ sudo python facetrack.py
```
The above script will track the known face using webcam mounted on Servo Pan/Tilt system. The servo system will adjust it's position continuously to center the known face.

> Limitation: Webcam can only track the first known face at a time.

[Link to Blog](http://www.96boards.org/blog/part-3-home-surveillance-project-96boards/)

