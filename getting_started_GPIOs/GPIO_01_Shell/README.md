# General Purpose Input/Output

GPIO provides the basic Input and Output access to the physical world for DragonBoard. GPIO pins can perform 'read' and
'write' operation for controlling devices connected to DragonBoard.

DragonBoard provides access to GPIO pins through 40pin **Low Speed Expansion Header** available on all CE boards.

## GPIO access through Command Line

The following instructions are applicable to all Linux based distributions and is based on sysfs interface.

To access the GPIOs through the Linux shell, open the terminal (start menu > other > LXTerminal; right click this to add shortcut to your desktop if you desire) and give yourself super user access:

```shell
$ sudo su
```

Giving yourself superuser access will allow you to modify the GPIOs (if you get an access denied for a GPIO, this means you’re trying to modify a GPIO the board is using for itself)

Once you have superuser access, navigate to the gpio folder with the following command:

```shell
# cd /sys/class/gpio
```

Before accessing any GPIO, it needs to be exported using the following command:

```shell
# echo 36 > export
```

For mapping pins to LS expansion header pins,
consult the board documentation availabe in [Products page](http://www.96boards.org/products/ce/)

> **DragonBoard410c:** 36, 12, 13, 69, 115, 4, 24, 25, 35, 34, 28, 33  

After exporting GPIO, move into that gpio directory
GPIO36 is pin 23 on the low speed expansion header
```shell
# cd gpio36
```

Following command returns the direction of GPIO
```shell
# cat direction
```

Following command sets the direction of GPIO as input
```shell
# echo in > direction
```

Following command returns 0 if the pin is off, 1 if the pin is on
```shell
# cat value
```
Following command sets the direction of GPIO as output
```shell
# echo out > direction
```
Once the GPIO is set as output, following command sets value of GPIO as high.
```shell
# echo 1 > value
```
Following command sets value of GPIO as low.
```shell
# echo 0 > value
```

Using a multimeter set to measuring voltage, you can probe the pin you are toggleing along with one of the ground nodes (Pins 1,2,39, and 40), to watch the voltage switch between ~1.8V and 0V.

## Next: GPIO access through MRAA library

