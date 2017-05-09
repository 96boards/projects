# accel

This project demonstrates interfacing of Accelerometer and RGB LCD with Dragonboard 410C using libupm and libmraa.
LCD will show the XYZ acceleration readings with blue background in ideal mode. If shake is detected, color will change
to Red and if tap is detected, color will change to Green.

### Hardware required:

1. Dragonboard 410c or any of 96Boards CE
2. Sensors Mezzanine
3. MMA7600 sensor
4. RGB LCD
5. Connecting cables

### Building and Running:

``` shell
$ git clone https://github.com/96boards/projects.git
$ cd projects
$ cd accel
$ make
$ ./bin
```

### Conclusion:

Following output can be observed by running the executable.

#### Acceleration:
Change the sensor position to see acceleration readings
#### Tap/Shake detection:
Mount the sensor on a plain surface and tap/shake it to obeserve the color change in LCD
