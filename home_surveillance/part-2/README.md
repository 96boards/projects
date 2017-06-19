# Part 2: Facial recognition using OpenCV

Install OpenCV on 96Boards and implement face detection / recognition. Following are the steps necessary
to acheive facial recognition:

# Table of Contents

- [1) Hardware](#hardware)
   - [1.1) Hardware requirements](#hardware-requirement)
   - [1.2) Hardware setup](#hardware-setup)
- [2) Software](#software)   
   - [2.1) Operating System](#operating-system)
   - [2.2) Package dependencies](#software-dependencies)
   - [2.3) OpenCV Installation](#opencv-installation)
- [3) Project Start](#project-start)
   - [3.1) Create dataset](#create-dataset)
   - [3.2) Train the dataset](#train-the-dataset)
   - [3.3) Implement face detection](#implement-face-detection)

***

# 1) Hardware

## 1.1 Hardware requirements

- [Dragonboard 410c](http://www.96boards.org/product/dragonboard410c/)
- [96Boards Compliant Power Supply](http://www.96boards.org/product/power/)
- USB Webcam

## 1.2 Hardware setup

- DragonBoard 410 is powered off
- Connect USB webcam
- Connect I/O devices (Monitor, Keyboard, etc...)
- Power on your DragonBoard 410c with 96Boards compliant power supply

# 2) Software

## 2.1 Operating System

- [Linaro Debian based OS (latest)](https://github.com/96boards/documentation/blob/master/ConsumerEdition/DragonBoard-410c/Downloads/Debian.md)

## 2.2 Package Dependencies

``` shell
$ sudo apt-get update
$ sudo apt-get install build-essential

$ sudo apt-get install cmake pkg-config libjpeg-dev libtiff5-dev \
libpng12-dev libavcodec-dev libavformat-dev libswscale-dev libv4l-dev \
libjasper-dev python2.7-dev python-pip python-setuptools

$ sudo easy_install pillow
```

> Note: For release >= 17.04, some of the packages needs to be installed from previous release. So, execute the following commands
if you are using latest release (>=17.04)

```shell
$ echo "deb http://deb.debian.org/debian jessie main" | sudo tee -a /etc/apt/sources.list
$ echo "deb-src http://deb.debian.org/debian jessie main" | sudo tee -a /etc/apt/sources.list
$ sudo apt-get update
```

[Return to initial package dependencies](#package-dependencies)

## 2.3 OpenCV Installation

``` shell
$ git clone https://github.com/opencv/opencv.git
$ git clone https://github.com/opencv/opencv_contrib.git
$ cd opencv_contrib
$ git checkout 3.2.0
$ cd ../opencv
$ git checkout 3.2.0
```
###### Turn ON SWAP partition:

``` shell
$ dd if=/dev/zero of=~/swapfile bs=1M count=512
$ sudo mkswap ~/swapfile
$ sudo swapon ~/swapfile
```
###### Build the source:

``` shell
$ mkdir build
$ cd build
$ cmake -D CMAKE_BUILD_TYPE=RELEASE -DCMAKE_INSTALL_PREFIX=/usr/local -DOPENCV_EXTRA_MODULES_PATH=<opencv_contrib>/modules ../
```

> Note: Replace <opencv_contrib> with the path of the cloned *opencv_contrib* directory.

```shell
$ make -j4
$ sudo make install
```

# 3) Project Start

```shell
$ git clone https://github.com/96boards/projects.git
$ cd projects/home_surveillance/part-2
```

## 3.1 Creating dataset

```shell
$ mkdir dataset
$ sudo python dataset.py
```
Enter the user ID of known person. Execute this script multiple times with different IDs for creating multiple person's dataset.

## 3.2 Training the dataset

```shell
$ mkdir trainer
$ sudo python trainer.py
```

## 3.3 Implement face detection

```shell
$ sudo python facedetect.py
```

* [Link to Blog](http://www.96boards.org/blog/part-2-home-surveillance-project-96boards/)
