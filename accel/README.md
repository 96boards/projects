# accel

This project demonstrates interfacing of Accelerometer and RGB LCD with Dragonboard 410C using libupm and libmraa.
LCD will show the XYZ acceleration readings with blue background in ideal mode. If shake is detected, color will change
to Red and if tap is detected, color will change to Green.

# Table of Contents
- [1) Hardware requirements](#1-hardware-requirements)
- [2) Software](#2-software) 
   - [2.1) Operating System](#21-operating-system)
   - [2.2) Package Dependencies](#22-package-dependencies)
- [3) Building and Running](#3-building-and-running)
- [4) Conclusion](#4-conclusion)
   - [4.1) Acceleration](#41-acceleration)
   - [4.2) Tap/Shake detection](#42-tapshake-detection)

# 1. Hardware requirements:

1. [Dragonboard 410c or any of 96Boards CE](http://www.96boards.org/product/dragonboard410c/)
2. [Sensors Mezzanine](http://www.96boards.org/product/sensors-mezzanine/)
3. [MMA7600 sensor](http://wiki.seeed.cc/Grove-3-Axis_Digital_Accelerometer-1.5g/)
4. [RGB LCD](https://www.seeedstudio.com/Grove-LCD-RGB-Backlight-p-1643.html)
5. Connecting cables

# 2. Software

## 2.1 Operating System

- [Linaro Debian based OS (latest)](https://github.com/96boards/documentation/blob/master/ConsumerEdition/DragonBoard-410c/Downloads/Debian.md)

## 2.2 Package Dependencies 

1. MRAA Library
```
$ sudo apt-get install libupm-dev
```
2. UPM Library
```
$ sudo apt-get install libmraa-dev
```

# 3. Building and Running:

``` shell
$ git clone https://github.com/96boards/projects.git
$ cd projects
$ cd accel
$ make
$ ./bin
```

# 4. Conclusion:

Following output can be observed by running the executable.

## 4.1 Acceleration:
Change the sensor position to see acceleration readings
## 4.2 Tap/Shake detection:
Mount the sensor on a plain surface and tap/shake it to obeserve the color change in LCD
