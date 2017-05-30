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
### Creating dataset

```shell
$ mkdir dataset
$ sudo python dataset.py
```
### Training the dataset

```shell
$ mkdir trainner
$ sudo python trainner.py
```

### Implement face detection

```shell
$ sudo python facedetect.py
```

* [Link to Blog](http://www.96boards.org/blog/part-2-home-surveillance-project-96boards/)
