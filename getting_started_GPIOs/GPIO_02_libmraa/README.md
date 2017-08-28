# Running a Libmraa Python example on your DragonBoard 410c

This guide will help you execute a simple python code using libmraa. 

## Step 1: Hardware Setup:

### Hardware Requirements:

1. [DragonBoard 410c](https://www.96boards.org/product/dragonboard410c)
2. [Grove Sensors Mezzanine](http://www.96boards.org/product/sensors-mezzanine/)
3. [LED](https://www.seeedstudio.com/Grove-LED-p-767.html)
4. [Grove Universal 4 Pin Cable](https://www.seeedstudio.com/Grove---Universal-4-Pin-20cm-Unbuckled-Cable-%285-PCs-Pack%29-p-749.html)
5. [Grove Touch Sensor Module](https://www.seeedstudio.com/Grove-Touch-Sensor-p-747.html)

### Hardware Connections:

1. Make sure that the DragonBoard 410c is initially unplugged (powered off)
2. Conect the Sensors Mezzanine  to DragonBoard 410c through the 40 pin low-speed expansion connector. Mezzanine board (male pins) will match 1-to-1 with female pins on DragonBoard 410c connector. Make sure all 40 pins are lined up properly before moving to next step.
3. If you wish to use the serial console from your host machine, connect USB cable to host machine and microUSB on mezzanine board (USB Type-A end of cable connects to host machine, microUSB end of cable connects to microUSB port on Mezzanine.
If you wish to use the Linux Desktop, connect a mouse and a keyboard on the USB ports available on the DragonBoard. USe the HDMI port to connect your device to a monitor. 
4. Attach the LED to GPIO 23.
5. Attach the Grove Touch Sensor Module to Grove connector G3 on the Sensors Mezzanine.

## Step 2: Software Setup:

### Downloading and installing libmraa (if you don't already have it)

> NOTE: If you are using a DragonBoard 410c with [Debian OS from Linaro](http://www.96boards.org/documentation/ConsumerEdition/DragonBoard-410c/Downloads/Debian.md), you already have libmraa.

If you get the following error, 
```
ImportError: No Module named 'mraa'
```
or if you are unsure, you should run the following commands to make sure you have the correct gpio library.
```
$ git clone https://github.com/intel-iot-devkit/mraa
$ cd mraa
$ mkdir build
$ cd build
$ cmake ..
$ make
$ sudo make install
$ sudo ldconfig /usr/local/lib/
```
### Getting the sample code and running it
This sample code is meant to blink an LED at a certain time interval. Follow the steps below to execute the code.

```
$ cd mraa
$ cd examples
$ cd python
$ vim blink-io8.py
```
You can go through the code in order to understand how it works. Since, we are connecting our LED to GPIO 23, we will have to edit that in the code at line 28.
```
x = mraa.Gpio(23)
```

##Now, execute the code

```
$ sudo python blink-io8.py
```

Congratulations! You have executed your first python code using libmraa.
Now that you have tried blinking the LED, lets tie it to an input and blink it using the touch sensor.
Create a new file named touch_blink.py, and copy the below code into the file.

```
import mraa
print (mraa.getVersion())

led = mraa.Gpio(23)
led.dir(mraa.DIR_OUT)
led.write(0)

touch = mraa.Gpio(29)
touch.dir(mraa.DIR_IN)


while True:
	touchButton = int(touch.read())
	if(touchButton == 1):
		led.write(1)
	else:
		led.write(0)

```

##Now, execute the code

```
$ sudo python touch_blink.py
```

Congratulations! You have used both inputs and outputs using python code and libmraa gpio library.
To try out more projects with GPIO's clone the projects repository with:

```	
$ git clone https://github.com/96boards/projects.git
```

Reference : [96Boards projects repository](https://github.com/96boards/projects)
