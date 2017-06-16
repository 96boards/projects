# Digital Hourglass

The Digital Hourglass project implements a count up timer which takes in user input for the time to be 
measured and prints a character on the display at certain intervals till the time is up. The project 
goes through some of the basic concepts like connecting the Sensors Mezzanine board with the DragonBoard, 
interfacing an LCD with the board and installing the necessary libraries.

## Hardware required:

1. [DragonBoard 410c](http://www.96boards.org/product/dragonboard410c/)
2. [Power Supply](https://www.amazon.com/Adapter-Regulated-Supply-Copper-String/dp/B015G8DZK2)
2. [Sensors Mezzanine](http://www.96boards.org/product/sensors-mezzanine/)
3. [Micro USB Cable](https://www.amazon.com/AmazonBasics-USB-Male-Micro-Cable/dp/B01EK87A82/ref=sr_1_3?ie=UTF8&qid=1497618343&sr=8-3&keywords=micro%2Busb&th=1)
4. [Grove-LCD 16x2 RGB Backlight and a grove cable](https://www.seeedstudio.com/Grove-LCD-RGB-Backlight-p-1643.html)

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
