# Part 2: Facial recognition using OpenCV

Install OpenCV on 96Boards and implement face detection / recognition. Following are the steps necessary
to acheive facial recognition.

If you would like to read more about this project, please visit [this blog](http://www.96boards.org/blog/part-2-home-surveillance-project-96boards/) written by Manivannan Sadhasivam.

# Table of Contents

- [1) Hardware](#1-hardware)
   - [1.1) Hardware requirements](#11-hardware-requirements)
   - [1.2) Hardware setup](#12-hardware-setup)
- [2) Software](#2-software)   
   - [2.1) Operating System](#21-operating-system)
   - [2.2) Package dependencies](#22-package-dependencies)
   - [2.3) OpenCV Installation](#23-opencv-installation)
- [3) Project Execution](#3-project-execution)
   - [3.1) Create dataset](#31-creating-dataset)
   - [3.2) Train the dataset](#32-training-dataset)
   - [3.3) Implement face detection](#33-implement-face-detection)

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

> Note: For release >= 17.04, some of the packages needs to be installed from previous releases. Execute the following commands
if you are using latest release (>=17.04)

```shell
$ echo "deb http://deb.debian.org/debian jessie main" | sudo tee -a /etc/apt/sources.list
$ echo "deb-src http://deb.debian.org/debian jessie main" | sudo tee -a /etc/apt/sources.list
```
The above command adds previous release ***Debian 8*** a.k.a ***Jessie*** to the known list of sources. This is useful for fetching packages from previous release if the current release doesn't have it.

Get the latest of all known packages from sources listed in /etc/apt/sources.list

```shell
$ sudo apt-get update
$ sudo apt-get upgrade
```
#### Install the required packages

```shell
$ sudo apt-get install build-essential cmake pkg-config libjpeg-dev libtiff5-dev \
libpng12-dev libavcodec-dev libavformat-dev libswscale-dev libv4l-dev \
libjasper-dev python2.7-dev python-pip python-setuptools
$ sudo apt-get install libgtk2.0-dev

$ sudo easy_install pillow
```

## 2.3 OpenCV Installation

``` shell
$ git clone https://github.com/opencv/opencv.git
$ git clone https://github.com/opencv/opencv_contrib.git

# Checkout 3.2.0 branch from opencv_contrib
$ cd opencv_contrib
$ git checkout 3.2.0

# Checkout 3.2.0 branch from opencv
$ cd ../opencv
$ git checkout 3.2.0
```
###### Turn ON SWAP partition:

Use swapfile to prevent DragonBoard from running out of RAM. Follow the instructions [here](https://github.com/96boards/documentation/blob/master/ConsumerEdition/CE-Extras/Configuration/SDSwapSpace.md) for allocating swap space in SD card.

###### Build the source:

``` shell
$ mkdir build
$ cd build
```
Use CMAKE to configure the build environment. In order to make build much quicker, examples and tests have been excluded.

```shell
$ cmake -D CMAKE_BUILD_TYPE=RELEASE -DBUILD_EXAMPLES=OFF -DBUILD_opencv_apps=OFF -DBUILD_DOCS=OFF -DBUILD_PERF_TESTS=OFF -DBUILD_TESTS=OFF -DCMAKE_INSTALL_PREFIX=/usr/local -DENABLE_PRECOMPILED_HEADERS=OFF -DOPENCV_EXTRA_MODULES_PATH=<opencv_contrib>/modules ../
```

> Note: Replace <opencv_contrib> with the path of the cloned *opencv_contrib* directory.

Next, build OpenCV with 2 threads. *-j n* decides the number of threads involved in building the source. Ideally, threads should be equal to number of cores availabe in SoC. Since, DragonBoard is quad core you can have *-j 4* but it may cause the CPU to overheat. So, limit to 2 inorder to avoid freeze during build.

```shell
$ make -j 2
```
Install the compiled binaries and libraries to default location

```shell
$ sudo make install
```

# 3) Project Execution

```shell
## Clone the project source 
$ git clone https://github.com/96boards/projects.git
$ cd projects/home_surveillance/part-2
```

## 3.1 Creating dataset

```shell
$ mkdir dataset
```
*dataset.py* script tries to auto detect the source for USB webcam. It could be different on each board. 
For finding the correct video source, the script sends the following command to the operating system:

```shell
$ ls -lrt /dev/video*
```
Total number of availabe video sources will get listed. The one with latest modification time is the USB camera source.
For instance:

```shell
crw-rw----+ 1 root video 81, 1 Jun 20 18:58 /dev/video1
crw-rw----+ 1 root video 81, 0 Jun 20 18:58 /dev/video0
crw-rw----+ 1 root video 81, 2 Jun 21 03:15 /dev/video2
```
Here, video2 has the latest modification time of 03:15. So, this should be the interface for USB wecam as it was connected after boot. Other two intrefaces are for video cards initialized during boot time. In this case, the script will parse through the response lines and assign 2 to the variable "camNO".

If there are any errors related to the script not being able to identify the Webcam, simply unplug the webcam and connect it back to the USB and re-launch the following script.

```shell
$ sudo python dataset.py
```
Script will prompt the user to enter the users Name. Type Your name and press Enter. If multiple faces needs to be detected, it should be executed multiple times. The script will mantain the User's Id Vs Name in a CSV file "file.txt"
Everytime the user runs dataset.py, it updates file.txt, captures 30 instances of the face infront of camera and stores inside *dataset* directory. Both dataset.py and facedetect.py read from this file.txt csv file and use it as a look up to display the users name on the detected face.

For the sake of convineance, dataset.py also updates the training dataset seen in #3.2 below.
This way the user does not have to train the face detection every time they update the dataset. 
For educative purpose, the training script (trainer.py in ##3.2 below) is also seperately included to make the distinction between capturing the data using face detection and training the dataset to realize face recognition. 

## 3.2 Training dataset

Create trained dataset model for face recognition.

```shell
$ mkdir trainer
$ sudo python trainer.py
```
This script will create *trainer.yml* file inside *trainer* directory and will be used for facial recognition.

## 3.3 Implement face detection

```shell
$ sudo python facedetect.py
```
This script makes use of the created trained model *trainer.yml* to implement facial recognition. Once the script has been executed, it will detect the faces infront of the camera and if any of the face matches with the created dataset, the corresponding name will be shown. Otherwise *unknown* will be shown.
