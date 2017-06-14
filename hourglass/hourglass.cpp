/*
 * Author: Radhika Paralkar
 * Copyright (c) 2016 Linaro Ltd.
 * All rights reserved.
 *
 */

#include <iostream>
#include <string>
#include "../../include/upm/jhd1313m1.hpp"

#define I2C_BUS  0

using namespace std;
upm::Jhd1313m1* lcd;

int main()
{
	int interval, timer_time;
	lcd = new upm::Jhd1313m1(I2C_BUS, 0x3e, 0x62);


	lcd->clear();
	lcd->setColor(0x00,0x00,0xff); //blue
	lcd->setCursor(0,0); 
	lcd->write("Enter time in");
    lcd->setCursor(1,0);
    lcd->write("minutes...");

    cout << "Enter the time in minutes:" << endl;
    cin >> timer_time;

    interval = (timer_time*60)/30;

	lcd->clear();
    lcd->setColor(0xff, 0xff, 0xff);

    for(int i=0;i<2;i++)
    {
        for(int j=0;j<15;j++)
        {
                lcd->setCursor(i,j);
                lcd->write("*");
                sleep(interval);
        }
    }

    lcd->clear();
    lcd->write("TIME UP!!");
    sleep(10);

	delete lcd;
	return 0;
}




