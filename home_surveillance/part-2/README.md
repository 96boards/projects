# Part 2: Facial recognition using OpenCV

Install OpenCV on 96Boards and implement face detection using it. Following are the steps necessary
to acheive facial recognition:

* Create dataset
* Train the dataset
* Implement face detection

### Hardware requirements and setup

* Dragonboard410C
* USB Webcam

Connect USB webcam ,I/O devices (Monitor, Keyboard etc...) to Dragonboard and power up.

### Software dependencies

``` shell
$ sudo apt-get update
$ sudo apt-get install build-essential
```
---------------------------------------------------------------------------------------
For release >= 17.04, some of the packages needs to be installed from previous release. So, execute the following commands
if you are using latest release (>=17.04)
```shell
$ echo "deb http://deb.debian.org/debian jessie main" | sudo tee -a /etc/apt/sources.list
$ echo "deb-src http://deb.debian.org/debian jessie main" | sudo tee -a /etc/apt/sources.list
$ sudo apt-get update
```
---------------------------------------------------------------------------------------
```shell
$ sudo apt-get install cmake pkg-config libjpeg-dev libtiff5-dev \
libpng12-dev libavcodec-dev libavformat-dev libswscale-dev libv4l-dev \
libjasper-dev python2.7-dev python-pip python-setuptools

$ sudo easy_install pillow
```
### OpenCV - Installation

``` shell
$ git clone https://github.com/opencv/opencv.git
$ git clone https://github.com/opencv/opencv_contrib.git
$ cd opencv_contrib
$ git checkout 3.2.0
$ cd ../opencv
$ git checkout 3.2.0
```
Turn ON SWAP partition:

``` shell
$ dd if=/dev/zero of=~/swapfile bs=1M count=512
$ sudo mkswap ~/swapfile
$ sudo swapon ~/swapfile
```
Build the source:

``` shell
$ mkdir build
$ cd build
$ cmake -D CMAKE_BUILD_TYPE=RELEASE -DCMAKE_INSTALL_PREFIX=/usr/local -DOPENCV_EXTRA_MODULES_PATH=<opencv_contrib>/modules ../
```
Replace <opencv_contrib> with the path of the cloned *opencv_contrib* directory.
```shell
$ make -j4
$ sudo make install
```
### Cloning the project

```shell
$ git clone https://github.com/96boards/projects.git
$ cd projects/home_surveillance/part-2
```

### Creating dataset

```shell
$ mkdir dataset
$ sudo python dataset.py
```
Enter the user ID of known person. Execute this script multiple times with different IDs for creating multiple person's dataset.

### Training the dataset

```shell
$ mkdir trainer
$ sudo python trainer.py
```

### Implement face detection

```shell
$ sudo python facedetect.py
```

* [Link to Blog](http://www.96boards.org/blog/part-2-home-surveillance-project-96boards/)
