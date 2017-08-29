# Setting up Arduino Toolchain in DragonBoard410c

This guide will teach user to access the Arduino toolchain in DragonBoard 410c using a Sensors Mezzanine.  

## Hardware requirements:

1. [DragonBoard 410c](https://www.96boards.org/product/dragonboard410c)
2. [Grove Sensors Mezzanine](http://www.96boards.org/product/sensors-mezzanine/)
3. USB to microUSB cable

## Step 1: Hardware Setup:

There are two ways in which we can use the Arduino toolchain on the DragonBoard410c. One is through serial console using the Sensors Mezzanine and a USB to mircoUSB cable and the other is to use a monitor, keyboard and mouse with the DragonBoard410c and use the available desktop. 

To begin with the first one, follow these steps:
1. Make sure that the DragonBoard 410c is initially unplugged (powered off)
2. Conect the Sensors Mezzanine  to DragonBoard 410c through the 40 pin low-speed expansion connector. Mezzanine board (male pins) will match 1-to-1 with female pins on DragonBoard 410c connector. Make sure all 40 pins are lined up properly before moving to next step.
3. Connect USB cable to host machine and microUSB on mezzanine board (USB Type-A end of cable connects to host machine, microUSB end of cable connects to microUSB port on Mezzanine.

> NOTE: Make sure all 40 mezzanine pins (male) are lined up with all 40 input pins (female) on DragonBoard 410c low-speed connetor

> NOTE: USB Type-A to microUSB cable should run from your host machine to the microUSB port on the Sensors Mezzanine, NOT the DragonBoard 410c.

And for the second method, the 96Boards Debian images come with the LXDE desktop environment already installed. It can be used as a normal Linux desktop computer if you attach a keyboard, mouse and monitor.

1. Make sure that the DragonBoard 410c is initially unplugged (powered off)
2. Conect the Sensors Mezzanine  to DragonBoard 410c through the 40 pin low-speed expansion connector. Mezzanine board (male pins) will match 1-to-1 with female pins on DragonBoard 410c connector. Make sure all 40 pins are lined up properly before moving to next step.
3. Connect a mouse and a keyboard on the USB ports available on the DragonBoard. USe the HDMI port to connect your device to a monitor. 

## Step 2: Software setup

### Serial Console:
In this step we will access the terminal on your host machine to make sure the Mezzanine device (and DragonBoard) are detected by the host machine.

1. DragonBoard is still powered off
2. Open the terminal application on your host machine.
3. Type in the following command:

```shell
$ ls /dev/tty*
```

If a device is detected, you will see a long list of devices. One of these devices should be recognized as the following (or similar):

For Linux:

`ttyUSB0`

For Mac OSX

`tty.usbserial-08-15`

Once you have confirmed your device is being recognized by the host machine, you can move on to the next step.

> NOTE: You may want to unplug and plug back in the USB Type-A end of the cable from you host machine while running the above command in each time. This might help you notice when the device is detected.

Enter the following command:

For Linux

`$ screen /dev/ttyUSB0 115200`

For Mac OSX

`$ screen /dev/tty.usbserial-08-15 115200`

When this command is executed, your terminal will clear and you should only see black.

3. Plug your DragonBoard 410c into power

Now to install the arduino toolchain,
```
$ sudo apt-get install arduino-mk arduino
```

### Linux Desktop on DrgonBoard:

 Use the “Terminal” application to get a command prompt. Now to install the arduino toolchain,
```
$ sudo apt-get install arduino-mk arduino
```
When you go into the Application Menu->Programming->Arduino IDE, you can open the Arduino IDE. 

## Step 3: Testing a sample code on the toolchain

In this step you will use the existing sample code in order to run a simple application. To do so, first fetch the sample code. Now, based on the method you are using, you could either access the sample code via the terminal and use an editor like vim to edit it, or you could open up the Arduino IDE on your desktop and work with the code there.

```
$ git clone https://github.com/96boards/Starter_Kit_for_96Boards
```

## Serial Console:
```
$ cd Starter_Kit_for_96Boards
$ cd button_led
```
Add the Arduino.mk Makefile to the same directory:
```
$ ln -s /usr/share/arduino/Arduino.mk Makefile
```
Run the demo
Build and execute the program
```
$ make upload reset_stty
```
## Linux Desktop:

Open the sample code file in the Arduino IDE. Click on the Verify Button in order to verify and compile the code. Click on the Upload button to upload the code on the DragonBaord.

Congratulations! You are now using the Arduino Toolchain!
