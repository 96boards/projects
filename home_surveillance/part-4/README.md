# Part 4 - Setting up your Amazon Web Service (AWS) Cloud Service

Set up streaming of data from Dragonboard to AWS S3 bucket. AWS account and S3 needs to be configured
prior executing the script.

### Hardware requirements

* Dragonboard410C
* USB Webcam

### Software Dependencies
 
Installed the dependencies mentioned in [Part-2](../part-2) along with the following:

``` shell
$ sudo pip install boto3
```
### Stream data to S3 bucket

``` shell
$ git clone https://github.com/96boards/projects.git
$ cd projects/home-surveillance/part-4
```
Place the trained dataset and haarcascade_frontalface_default.xml to this directory

``` shell
$ mkdir captured
$ sudo python streamface.py
```
[Link to Blog](http://www.96boards.org/blog/part-4-home-surveillance-project-96boards/)
