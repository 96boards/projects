/*
 * Digital Hourglass
 * Author: Radhika Paralkar
 * Copyright (c) 2017 Linaro Ltd.
 * All rights reserved.
 ********************************
 * 
 * I2C0 --> LCD
 */

#include <iostream>
#include <string>
#include "upm/jhd1313m1.hpp"

#define I2C_BUS  0

using namespace std;
upm::Jhd1313m1* lcd;

int main()
{
    int interval, timer_time;
    lcd = new upm::Jhd1313m1(I2C_BUS, 0x3e, 0x62);

    /* Clear the LCD and display initial message */
    lcd->clear();
    lcd->setColor(0x00,0x00,0xff); //Blue
    lcd->setCursor(0,0); 
    lcd->write("Enter time in");
    lcd->setCursor(1,0);
    lcd->write("minutes...");

    /* Obtain time in minutes via basic input */
    cout << "Enter the time in minutes:" << endl;
    cin >> timer_time;

    /* Convert time to seconds and calculate appropriate
    intervals for sleep (in seconds) */
    interval = (timer_time*60)/30;

    /* Clear the initial message after obtaining user input */
    lcd->clear();
    lcd->setColor(0xff, 0xff, 0xff); //White

    /* The two for loops move the cursor position after each
    interval and print a character on the display*/
    for(int i=0;i<2;i++)
    {
        for(int j=0;j<15;j++)
        {
                lcd->setCursor(i,j);
                lcd->write("*"); //Could be any character of your choice
                sleep(interval);
        }
    }

    /* Clear display to print final message */
    lcd->clear();
    lcd->write("TIME UP!!");
    sleep(10);

    /* Free allocated memory to avoid memory leaks */
    delete lcd;
    return 0;
}




