# Magic 8 Ball
The Magic 8 Ball application displays messages on the LCD when the touch sensor module is tapped.
There are 20 statements out of which any one can appear randomly at each tap on the sensor. So ask away!


## Hardware required:

1. DragonBoard 410c
2. Power Supply
3. Sensors Mezzanine
4. Micro USB Cable
5. Grove-LCD 16x2 RGB Backlight
6. Grove Touch Sensor Module
7. Connecting cables

## Package dependencies:

1. MRAA Library
2. UPM Library

```shell
$ sudo apt-get install libmraa-dev
$ sudo apt-get install libupm-dev
```

## Building and Running:

```shell
$ git clone https://github.com/96boards/projects.git      
$ cd projects	
$ cd magic8																												
$ make																															
$ ./magic8
```

## Conclusion:

When the executable is run, the application displays an initial message on the LCD and waits for the sensor to be tapped.
With each tap, a new statement is displayed. These statements can be modified by the user in the code.
