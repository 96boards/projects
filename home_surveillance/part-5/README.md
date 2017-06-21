# Part 5 - Home Surveillance

Final part of the Home Surveillance project. This part includes webcam tracking of known faces and alerting the user if a 
blacklisted faces has been identified. Also, remote streaming the webcam using Python's Flask micro server framework.

If you would like to read more about this project, please visit [this blog](http://www.96boards.org/blog/part-5-home-surveillance-project-96boards/) written by Manivannan Sadhasivam.

# Table of Contents

- [1) Hardware](#1-hardware)
   - [1.1) Hardware requirements](#11-hardware-requirements)
   - [1.2) Hardware setup](#12-hardware-setup)
- [2) Software](#2-software)   
   - [2.1) Operating System](#21-operating-system)
   - [2.2) Package dependencies](#22-package-dependencies)
   - [2.3) Create SNS topic](#23-create-sns-topic)
   - [2.4) Update Topic policy](#24-update-topic-policy)
   - [2.5) Create Subscription](#25-create-subscription)
   - [2.6) Create Notification for blacklisted faces](#26-create-notification-for-blacklisted-faces)
   - [2.7) Port forwarding in router](#27-port-forwarding-in-router)
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
- Connect Servo Mount to Sensors Mezzanine by following [Part-3](../part-3)
- Connect USB webcam
- Connect I/O devices (Monitor, Keyboard, etc...)
- Power on your DragonBoard 410c with 96Boards compliant power supply

# 2) Software

## 2.1 Operating System

- [Linaro Debian based OS (latest)](https://github.com/96boards/documentation/blob/master/ConsumerEdition/DragonBoard-410c/Downloads/Debian.md)

## 2.2 Package Dependencies

Install the dependencies mentioned in [Part-2](../part-2), [Part-3](../part-3), and [Part-4](../part-4) 
along with the following:

```shell
sudo easy_install Flask
```
Execute the steps mentioned in [Part-2](../part-2), [Part-3](../part-3), and [Part-4](../part-4) before going further.

## 2.3 Create SNS topic
	
1. Go to AWS SNS (Simple notification Service) console https://console.aws.amazon.com/sns/v2/home 
2. Select Create Topic under SNS Dashboard
3. Enter Topic name of your choice. Eg: home_surveillance. You can leave display name as empty as we are going to use Email notification only
4. Click Create Topic. Created topic should be visible under Topics pane of SNS console
5. Copy the Topic’s ARN (Amazon Resource Name). This will be used to send notifications later
 
## 2.4 Update Topic policy
 
1. Under the Topics section, select the created topic by clicking the checkbox
2. Choose Edit topic policy under Actions
3. Select Everyone in both sections and click Update policy. This will allow every AWS users to publish and subscribe to this topic. Change it to specific users if you want to limit the accessibility.
 
## 2.5 Create Subscription
 
1. Select Subscriptions from SNS console
2. Click on Create Subscription
3. Paste the ARN we copied in above step
4. Select Email in Protocol dropdown
5. Type the email id in which you want to receive notifications in Endpoint
6. Click Create Subscription
 
Now you should have received a confirmation email from AWS in the email id given as Endpoint. Confirm the subscription to created topic by clicking Confirm Subscription. Once the subscription is confirmed, Subscription ARN should be visible under Subscriptions pane.
 
## 2.6 Create Notification for blacklisted faces
 
1. Go to AWS S3 console, https://console.aws.amazon.com/s3/ 
2. Select the bucket we’ve created in Part 4
3. Goto Properties tab and select Events
4. Click Add notification 
5. Enter name for the notification and choose Put under Events
6. Enter Prefix with the name you want to Blacklist. The same name should have a corresponding user ID in facedetect.py. For instance, Enter Mani if you didn’t change the script.
7. Enter .jpg in Suffix
8. Choose SNS topic under Send to
9. Choose the created SNS topic under SNS
10. Click Save

## 2.7 Port forwarding in router

Eg: TP Link **TD-W8968** port forwarding can be achieved by the following steps:
 
1. Go to router admin page at 192.168.1.1 and login with credentials
2. Go to Advanced Setup -> NAT -> Add
3. Enter name for Custom Service and Dragonboard’s IP in Server IP Address
4. External port Start/End: 80
5. Internal port Start/End: 5000
6. Click Apply

# 3) Project Execution

Clone the project source

```shell
$ git clone https://github.com/96boards/projects.git
$ cd projects/home_surveillance/part-5
```
Place the trained dataset and haarcascade_frontalface_default.xml created in [Part-2](../part-2) to current directory. Also, update the USB webcam video source as specified in [Part-2](../part-2/README.md#31-creating-dataset)

```shell
$ cp -r ../part-2/trainer ../part-2/haarcascade_frontalface_default.xml ./
$ mkdir captured
```
> Note: Make sure Servo Pan and Tilt system is setup properly as mentioned in [Part 3](../part-3)

```shell
$ sudo python home_surveillance.py
``` 
Now, if a known face is detected infront of webcam, following things will happen simultaneously.

1. First instance of the face will get uploaded to AWS S3 bucket
2. Webcam will track the known face
3. User will get email notification if the trigger event is set for that particular face as mentioned [here](#26-create-notification-for-blacklisted-faces)
4. Webcam ouput will get streamed 

Go to router's public ip to see the live face tracking and recognition
