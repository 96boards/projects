# Google Assistant using 96Boards
  The Google Assistant project aims at deploying Google Assistant on a DragonBoard 410c by 96Boards. Recently, Google released a software development kit (SDK) which allows third party developers to build their own Google Assistant on hardware of their choice. The SDK lets us add features such as hotword detection, voice control and natural language processing to devices of our choice. In this project we will make our own version of Google Assistant using a DragonBoard 410c, a USB mic and speakers.
  
  By the end of this project you should be able to interface an external microphone as well as bluetooth speaker with the DragonBoard, create and configure a Google Developer Project on Google Cloud Platform (a developer project basically gives your device, a DragonBoard in this case, access to the Google Assistant API), use and understand gRPC bindings. 

## Why this project?
  Google just released the SDK a few months ago so that the Assistant can be implemented on a wide range of platforms. So as 96Boards enthusiasts, it is essential that we test it out on one of the boards. It would be a great learning process and nothing beats the feeling of having a fully working project in your hands.

# Table of Contents
- [1) Hardware](#1-hardware)
   - [1.1) Hardware requirements](#11-hardware-requirements)
   - [1.2) Hardware setup](#12-hardware-setup)
- [2) Software](#2-software) 
   - [2.1) Operating System](#21-operating-system)
   - [2.2) Requirements](#22-requirements)
- [3) Configure Developers project](#3-configure-developers-project)
- [4) Account settings](#4-account-settings)
- [5) 

# 1) Hardware

## 1.1 Hardware requirements

- [Dragonboard 410c](http://www.96boards.org/product/dragonboard410c/)
- [96Boards Compliant Power Supply](http://www.96boards.org/product/power/)
- USB Microphone
- USB/Bluetooth Speakers

## 1.2 Hardware setup

- Make sure the DragonBoard is powered off
- Connect the USB Mic on the USB Port
- Connect I/O devices (Monitor, Keyboard, etc...)
- Power on your DragonBoard 410c with 96Boards compliant power supply
- When the system starts, open Bluetooth Manager and turn on the Bluetooth. Click on search so that the DragonBoard can start scanning for nearby devices. Once the device appears, right click on it and select pair. Finally, after pairing, click on connect. 
- To make sure the microphone and speakers are connected successfully, go to Application Menu -> Sound & Video -> PulseAudio Volume Control and check the input and output devices.

# 2) Software

## 2.1 Operating System

- [Linaro Debian based OS (latest)](https://github.com/96boards/documentation/blob/master/ConsumerEdition/DragonBoard-410c/Downloads/Debian.md)

## 2.2 Requirements
- For the first part of the project, we won't be installing any packages. All you will be needing is a Google Account. 

# 3) Configure Developers project
Follow these instructions in order to configure a Developer Project.

- Go to the the [projects page](https://console.cloud.google.com/cloud-resource-manager) on Google Cloud Platform and create a new project.
- In the [API manager page](https://console.developers.google.com/apis/api/embeddedassistant.googleapis.com/overview?project=dragon-assistant&duration=PT1H) search for the Google Assistant API and Enable it.
- Now we will create an [OAuth Client ID](https://console.developers.google.com/apis/credentials/oauthclient?project=dragon-assistant&pli=1). Select ‘Others’ and provide a product name and proceed to save. After you click on create, it will generate a dialog box with the client ID and secret. Next to the clientID, click on the download button and save the .json file in working directory of the DragonBoard.

You can find the video in the Images folder.
# 4) Account Settings
Open the [Activity Controls Page](https://myaccount.google.com/activitycontrols) and ensure that all of these switches are turned on. We will need each of these for the proper functioning of the project. 
- Web and App Activity
- Location History
- Device Information
- Voice and Audio Activity 




