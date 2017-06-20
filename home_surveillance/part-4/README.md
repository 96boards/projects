# Part 4 - Setting up your Amazon Web Service (AWS) Cloud Service

Set up streaming of data from Dragonboard to AWS S3 bucket. Following are the steps necessary
to stream detected faces to AWS.

If you would like to read more about this project, please visit [this blog](http://www.96boards.org/blog/part-4-home-surveillance-project-96boards/) written by Manivannan Sadhasivam.

# Table of Contents

- [1) Hardware](#1-hardware)
   - [1.1) Hardware requirements](#11-hardware-requirements)
   - [1.2) Hardware setup](#12-hardware-setup)
- [2) Software](#2-software)   
   - [2.1) Operating System](#21-operating-system)
   - [2.2) Package dependencies](#22-package-dependencies)
   - [2.3) Create S3 bucket](#23-create-s3-bucket)
   - [2.4) Set Object policy](#24-set-object-policy)
   - [2.5) Setup Boto SDK](#25-setup-boto-sdk)
- [3) Project Execution](#3-project-execution)

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
 
Install the dependencies mentioned in [Part-2](../part-2) along with the following:

``` shell
$ sudo easy_install boto3
$ sudo apt-get install awscli
```
## 2.3 Create S3 bucket
 
- Go to https://aws.amazon.com/ and select Sign in to console 
- Login to AWS using your Email and password (You’ll be redirected to console if you are already logged in)
- Select S3 from Storage. S3 console will get opened.
- Click on Create bucket button
- Enter Bucket name and Region in the opened window (Bucket name should be unique across all existing bucket names in S3). 
- Click Next
- If you want to customize your bucket, modify the properties otherwise keep on hitting Next until you find Create bucket button.
- In the final window, you should see the Bucket name, region, properties and permissions. Under permissions the instance of the login account should get displayed. Then, click Create bucket.
- The created bucket would get listed in the AWS S3 console.
 
## 2.4 Set Object policy
 
- Select the created bucket and click Permissions tab on top
- Select Bucket policy and paste the following policy in the text field

```shell 	
{
  "Id": "Policy1495783674300",
  "Version": "2012-10-17",
  "Statement": [
    {
      "Sid": "Stmt1495783672125",
      "Action": "s3:*",
      "Effect": "Allow",
      "Resource": "arn:aws:s3:::homesurveillance",
      "Principal": "*"
    }
  ]
}
```
- Replace ‘homesurveillance’ with your bucket name in the above policy and click Save.
- The above shown policy is just for demonstration purpose as it allows all AWS users to gain full access to the created bucket.
 
## 2.5 Setup Boto SDK
 
- Obtain the AWS key Id and secret key by following the instructions [here](https://aws.amazon.com/premiumsupport/knowledge-center/create-access-key/)

- Execute the below command to configure boto SDK with created AWS Id and key
 ```shell
 $ sudo aws configure
 ```
 - Enter AWS access Id and press Enter
 - Enter Secret key and press Enter 
 - Enter region name and press Enter
 - You can leave the default output format as [None]. Just press Enter
 - Now Boto SDK has been configured. The entered credentials could be found in ~/.aws/config
 
# 3) Project Execution

``` shell
$ git clone https://github.com/96boards/projects.git
$ cd projects/home-surveillance/part-4
```
Place the trained dataset and haarcascade_frontalface_default.xml to part-4 directory

``` shell
$ cp -r ../part-2/trainer ../part-2/haarcascade_frontalface_default.xml ./
$ mkdir captured
$ sudo python streamface.py
```
[Link to Blog](http://www.96boards.org/blog/part-4-home-surveillance-project-96boards/)
