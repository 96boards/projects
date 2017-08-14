# Self balancing Bot using 96Boards

Self balancing Bot also called as **Segway** is a bot based on **Inverted Pendulum** concept. It balances itself steadily by 
moving forth and back to counteract the fall. IMU (Inertial Measurement Unit) is used to measure the angle of the Bot for 
detecting the slope. Then, the motor position will be updated to keep the Bot steady. **PID** controller will be used to adjust 
the position of motors based on the angle calculated by **IMU**. All of the computations will be done using CE board and 
controlling the DC motor will be offloaded to Arduino present on Sensors Mezzanine. 

# Table of Contents
- [1) Hardware](#1-hardware)
   - [1.1) Hardware requirements](#11-hardware-requirements)
   - [1.2) Hardware setup](#12-hardware-setup)
- [2) Software](#2-software) 
   - [2.1) Operating System](#21-operating-system)
   - [2.2) Software Dependencies](#22-software-dependencies)
- [3) Measuring tilt using IMU](#3-measuring-tilt-using-imu)
- [4) Implementing PID controller](#4-implementing-pid-controller)
- [5) Controlling DC motors using Sensors Mezzanine](#5-controlling-dc-motors-using-sensors-mezzanine)
- [6) Establishing Bluetooth communication to CE board](#6-establishing-bluetooth-communication-to-ce-board)
- [7) Self Balancing Bot in action](#7-self-balancing-bot-in-action)

# 1) Hardware

## 1.1) Hardware requirements

- [96Boards CE](https://www.96boards.org/products/ce/)
- [96Boards Compliant Power Supply](http://www.96boards.org/product/power/)
- [Sensors Mezzanine](http://www.96boards.org/product/sensors-mezzanine/)
- [Chasis](https://nevonexpress.com/Self-Balancing-Robot-Chassis-Body-Diy.php)
- [IMU 6 DoF - MPU6050](http://www.amazon.in/GY-521-Mpu6050-Accelerometer-Arduino-REES52/dp/B008BOPN40/ref=sr_1_1?ie=UTF8&qid=1501573522&sr=8-1&keywords=mpu6050)
- [Motor Driver - L289N](http://www.amazon.in/Robodo-Electronics-Motor-Driver-Module/dp/B00N4KWYDE/ref=pd_sbs_328_1?_encoding=UTF8&psc=1&refRID=YESQPMRAEF73WTRQPRP1)
- [DC motor](http://www.rhydolabz.com/robotics-motor-drivers-c-155_162/751-metal-gearmotor-25dx54l-mm-lp-12v-with-48-cpr-encoder-p-2281.html)
- [Dc to DC Boost Converter](http://www.amazon.in/KitsGuru-Step-up-Adjustable-Booster-Current/dp/B00HV59922)
- [11.1v Battery for Board](http://robokits.co.in/batteries-chargers/lithium-ion-battery/li-ion-11.1v-2200mah-2c-with-inbuilt-charger-protection)
- [11.1v Battery for Motors](http://robokits.co.in/batteries-chargers/lithium-ion-battery/lithium-ion-rechargeable-battery-pack-11.1v-2200mah-2c)

## 1.2) Hardware setup

- Make sure the 96Boards CE is powered off
- Connect I/O devices (Monitor, Keyboard, etc...)
- Connect Sensors Mezzanine
- Power on your 96Boards CE with compatible power supply

# 2) Software

## 2.1) Operating System

- [Linaro Debian based OS (latest)](https://github.com/96boards/documentation/blob/master/ConsumerEdition/DragonBoard-410c/Downloads/Debian.md)

## 2.2) Software Dependencies

```
$ sudo apt-get update
$ sudo apt-get upgrade
```
# 3) [Measuring tilt using IMU](../imu)

# 4) Implementing PID controller

Coming soon...

# 5) Controlling DC motors using Sensors Mezzanine

Coming soon...

# 6) Establishing Bluetooth communication to CE board 

Coming soon...

# 7) Self Balancing Bot in action

Coming soon...
