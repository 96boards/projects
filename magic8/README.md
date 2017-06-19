# Magic 8 Ball
The Magic 8 Ball application displays messages on the LCD when the touch sensor module is tapped.
There are 20 statements out of which any one can appear randomly at each tap on the sensor. So ask away!


## Hardware required:

1. [DragonBoard 410c](http://www.96boards.org/product/dragonboard410c/)
2. [Power Supply](https://www.amazon.com/Adapter-Regulated-Supply-Copper-String/dp/B015G8DZK2)
3. [Sensors Mezzanine](http://www.96boards.org/product/sensors-mezzanine/)
4. [Micro USB Cable](https://www.amazon.com/AmazonBasics-USB-Male-Micro-Cable/dp/B01EK87A82/ref=sr_1_3?ie=UTF8&qid=1497618343&sr=8-3&keywords=micro%2Busb&th=1)
5. [Grove-LCD 16x2 RGB Backlight](https://www.seeedstudio.com/Grove-LCD-RGB-Backlight-p-1643.html)
6. [Grove Touch Sensor Module](https://www.seeedstudio.com/Grove-Touch-Sensor-p-747.html)

## Package dependencies:

1. MRAA Library
```
$ sudo apt-get install libupm-dev`
```
2. UPM Library
```
$ sudo apt-get install libmraa-dev`
```
## Building and Running:
```
$ git clone https://github.com/96boards/projects.git      
$ cd projects	
$ cd magic8																												
$ make																															
$ ./magic8
```

## Conclusion:

When the executable is run, the application displays an initial message on the LCD and waits for the sensor to be tapped.
With each tap, a new statement is displayed. These statements can be modified by the user in the code.
