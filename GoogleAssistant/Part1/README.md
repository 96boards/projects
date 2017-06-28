# Part 1
Part 1 provides a step by step guide in order to setup the board with the necessary hardware. Also, gives detailed instructions on how to create a project in Google Cloud Console, configure a developer project and manage the necessary account settings in order to have a functional Google Assistant application.

## Table of Contents
- [1) Hardware](#1-hardware)
   - [1.1) Hardware requirements](#11-hardware-requirements)
   - [1.2) Hardware setup](#12-hardware-setup)
- [2) Software](#2-software) 
   - [2.1) Operating System](#21-operating-system)
   - [2.2) Requirements](#22-requirements)
- [3) Configure Developers project](#3-configure-developers-project)
- [4) Account settings](#4-account-settings)

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

# 4) Account Settings
Open the [Activity Controls Page](https://myaccount.google.com/activitycontrols) and ensure that all of these switches are turned on. We will need each of these for the proper functioning of the project. 
- Web and App Activity
- Location History
- Device Information
- Voice and Audio Activity 

