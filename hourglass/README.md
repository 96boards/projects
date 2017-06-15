# Digital Hourglass

The Digital Hourglass project implements a count up timer which takes in user input for the time to be 
measured and prints a character on the display at certain intervals till the time is up. The project 
goes through some of the basic concepts like connecting the Sensors Mezzanine board with the DragonBoard, 
interfacing an LCD with the board and installing the necessary libraries.

## Hardware required:

1. DragonBoard 410c
2. Power Supply
3. Sensors Mezzanine
4. Micro USB Cable
5. Grove-LCD 16x2 RGB Backlight and a grove cable.

## Package dependencies:
UPM Library

## Building and Running:

```
$ git clone https://github.com/96boards/projects.git      
$ cd projects	
$ cd hourglass																													
$ make																															
$ ./hourglass
```																												


## Conclusion:

When the program is executed, the user is asked to enter the time in minutes. 30 '*' characters 
are printed on the display periodically based on the user input. Once the time is up, you will see 
a TIME UP message displayed on the LCD.
