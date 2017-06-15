/*
 * MAGIC 8 BALL
 * Author: Radhika Paralkar
 * Copyright (c) 2017 Linaro Ltd.
 * All rights reserved.
 ********************************
 * 
 * I2C0 --> LCD
 * GPIO G3 --> Touch Sensor Module
 */

#include <unistd.h>
#include <iostream>

#include "mraa.hpp"
#include "upm/jhd1313m1.hpp"

using namespace std;

int last_touch;

int main(void)
{
    int x;
    int touch;
	
    mraa::Gpio* touch_gpio = new mraa::Gpio(29);
    mraa::Result response;
    upm::Jhd1313m1* lcd = new upm::Jhd1313m1(0, 0x3e, 0x62);

    /* Clear the display and print initial message */
    lcd->clear();
    lcd->setColor(0x00,0x00,0xff); //Blue
    lcd->setCursor(0,0); 
    lcd->write("Ask question");
    lcd->setCursor(1,0);
    lcd->write("and press");

    while(true) 
    {
	/* Read the sensor value to check for touch */
        touch = touch_gpio->read();
        if (touch == 1 && last_touch == 0) 
        {
	    /* This will generate a random number between 0-19 */
	    x = rand() % 20; 
	    
	    /* Prints out the number on the serial console. 
	    Only for verification, not necessary */
	    cout << "Pressed! " << x << endl;
	    
	    /* Each number has a statement associated with it
	    which will be displayed on the LCD when that particular
	    number is generated */
	    switch(x)
	    {
		case 0:
		lcd->clear();
		lcd->setColor(0x00,0x00,0xff); 
		lcd->setCursor(0,0); 
		lcd->write("As I see it, yes");
		break;

		case 1:
		lcd->clear();
		lcd->setColor(0x00,0x00,0xff);
		lcd->setCursor(0,0); 
		lcd->write("Ask again later");
		break;

		case 2:
		lcd->clear();
		lcd->setColor(0x00,0x00,0xff);
		lcd->setCursor(0,0); 
		lcd->write("Better not tell");
		lcd->setCursor(1,0);
    		lcd->write("you now");
    		break;

		case 3:
		lcd->clear();
		lcd->setColor(0x00,0x00,0xff); 
		lcd->setCursor(0,0); 
		lcd->write("Cannot predict");
		lcd->setCursor(1,0);
    		lcd->write("now");
    		break;

		case 4:
		lcd->clear();
		lcd->setColor(0x00,0x00,0xff); 
		lcd->setCursor(0,0); 
		lcd->write("Concentrate and");
		lcd->setCursor(1,0);
   		lcd->write("ask again");
    		break;

		case 5:
		lcd->clear();
		lcd->setColor(0x00,0x00,0xff); 
		lcd->setCursor(0,0); 
		lcd->write("Dont count on it");
   		break;

		case 6:
		lcd->clear();
		lcd->setColor(0x00,0x00,0xff);
		lcd->setCursor(0,0); 
		lcd->write("It is certain");
   		break;

		case 7:
		lcd->clear();
		lcd->setColor(0x00,0x00,0xff);
		lcd->setCursor(0,0); 
		lcd->write("It is decidedly");
		lcd->setCursor(1,0);
    		lcd->write("so");
    		break;

		case 8:
		lcd->clear();
		lcd->setColor(0x00,0x00,0xff); 
		lcd->setCursor(0,0); 
		lcd->write("Most likely");
    		break;

		case 9:
		lcd->clear();
		lcd->setColor(0x00,0x00,0xff);
		lcd->setCursor(0,0); 
		lcd->write("My reply is no");
    		break;

		case 10:
		lcd->clear();
		lcd->setColor(0x00,0x00,0xff); 
		lcd->setCursor(0,0); 
		lcd->write("My sources say");
		lcd->setCursor(1,0);
    		lcd->write("no");
    		break;

		case 11:
		lcd->clear();
		lcd->setColor(0x00,0x00,0xff);
		lcd->setCursor(0,0); 
		lcd->write("Outlook good");
    		break;

		case 12:
		lcd->clear();
		lcd->setColor(0x00,0x00,0xff);
		lcd->setCursor(0,0); 
		lcd->write("Outlook not so");
		lcd->setCursor(1,0);
    		lcd->write("good");
    		break;

		case 13:
		lcd->clear();
		lcd->setColor(0x00,0x00,0xff); 
		lcd->setCursor(0,0); 
		lcd->write("Reply hazy, try");
		lcd->setCursor(1,0);
    		lcd->write("again");
    		break;

		case 14:
		lcd->clear();
		lcd->setColor(0x00,0x00,0xff); 
		lcd->setCursor(0,0); 
		lcd->write("Signs point to");
		lcd->setCursor(1,0);
    		lcd->write("yes");
    		break;

		case 15:
		lcd->clear();
		lcd->setColor(0x00,0x00,0xff);
		lcd->setCursor(0,0); 
		lcd->write("Very doubtful");
    		break;

		case 16:
		lcd->clear();
		lcd->setColor(0x00,0x00,0xff);
		lcd->setCursor(0,0); 
		lcd->write("Without a doubt");
    		break;

		case 17:
		lcd->clear();
		lcd->setColor(0x00,0x00,0xff); 
		lcd->setCursor(0,0); 
		lcd->write("Yes");
    		break;

		case 18:
		lcd->clear();
		lcd->setColor(0x00,0x00,0xff); 
		lcd->setCursor(0,0); 
		lcd->write("Yes - definitely");
    		break;

		case 19:
		lcd->clear();
		lcd->setColor(0x00,0x00,0xff); 
		lcd->setCursor(0,0); 
		lcd->write("You may rely on");
		lcd->setCursor(1,0);
    		lcd->write("it");
    		break;
	    }
            usleep(100000);
        }
	/* Save the previous state before running the while loop again */
        last_touch = touch;
    }
    /* Delete allocated memory */
    delete touch_gpio;
    delete lcd;
    return 0;
}
