# Part 2: Facial recognition using OpenCV

Install OpenCV on 96Boards and implement face detection using it. Following are the steps necessary
to acheive facial recognition:

* Create dataset
* Train the dataset
* Implement face detection

### Hardware requirements

* Dragonboard410C
* USB Webcam

### Software dependencies

``` shell
$ sudo apt-get install build-essential cmake pkg-config libjpeg-dev libtiff5-dev \
libpng12-dev libavcodec-dev libavformat-dev libswscale-dev libv4l-dev \ 
libjasper-dev python2.7-dev python-pip

$ pip install pillow
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
$ mkswap ~/swapfile
$ swapon ~/swapfile
```
Build the source:

``` shell
$ cd opencv
$ mkdir build
$ cd build
$ cmake -D CMAKE_BUILD_TYPE=RELEASE -DCMAKE_INSTALL_PREFIX=/usr/local -DOPENCV_EXTRA_MODULES_PATH=<opencv_contrib>/modules ../
$ make -j4
$ sudo make install
```
### Cloning the project

```shell
$ git clone https://github.com/96boards/projects.git
$ cd home_surveillance/part-2
```

### Creating dataset

```shell
$ mkdir dataset
$ sudo python dataset.py
```
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
