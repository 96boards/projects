 
/*
 * Author: Manivannan Sadhasivam
 * Copyright (c) 2017 Linaro Inc.
 * All rights reserved.
 *
 ************************************************************************************
 *
 * Accelerometer example 
 * 
 * I2C0--> Lcd
 * I2C1--> Accelerometer
 *
 */

#include "upm/jhd1313m1.hpp"
#include "upm/mma7660.hpp"

#define I2C_LCD_BUS 0
#define I2C_ACCEL_BUS 1
#define LCD_ADDR 0x3e
#define RGB_ADDR 0x62
#define ACCEL_ADDR 0x4c

using namespace std;
using namespace upm;

Jhd1313m1 *lcd;
MMA7660 *accel;

void print_accel()
{
	float ax, ay, az;
        char buffer[5];

        /* get acceleration from sensor */
        accel->getAcceleration(&ax, &ay, &az);

        /* display x aceleration */
        lcd->setCursor(1,0);
        snprintf(buffer, sizeof(buffer), "%f", ax);
        lcd->write(buffer);

        /* display y acceleration */
        lcd->setCursor(1,6);
        snprintf(buffer, sizeof(buffer), "%f", ay);
        lcd->write(buffer);

        /* display z acceleration */
        lcd->setCursor(1,12);
        snprintf(buffer, sizeof(buffer), "%f", az);
        lcd->write(buffer);
}

int main(void)
{
	int count;
	uint8_t reg;
	float ax, ay, az;
	char buffer[5];

	lcd = new upm::Jhd1313m1(I2C_LCD_BUS, LCD_ADDR, RGB_ADDR);
	accel = new MMA7660(I2C_ACCEL_BUS, ACCEL_ADDR);

	/* place device in standby mode so we can write registers */
	accel->setModeStandby();

	/* enable 64 samples per second */
	accel->setSampleRate(MMA7660::AUTOSLEEP_64);

	/* setup SR register */
	accel->writeByte(MMA7660::REG_SR, 0x00);
	
	/* setup tap threshold */
	accel->writeByte(MMA7660::REG_PDET, 0x44);

	/* setup tap debounce */
	accel->writeByte(MMA7660::REG_PD, 0x02);

	/* place device into active mode */
	accel->setModeActive();

	/* set background color as blue and display x, y z */
	lcd->setColor(0x00, 0x00, 0xff);
	lcd->setCursor(0,0);
	lcd->write("X:");
        lcd->setCursor(0,5);
        lcd->write("Y:");
        lcd->setCursor(0,12);
        lcd->write("Z:");


	while(1) {
		/* change color to red if shake is detected*/
		if (accel->tiltShake())
			lcd->setColor(0xff, 0x00, 0x00);

		/* change color to green if tap is detected*/
	        if (accel->tiltTap())
                	lcd->setColor(0x00, 0xff, 0x00);
	
		/* print acceleration readings */
		print_accel();
	
		/* sleep for 0.5s */
		usleep(500000);

		/* default to blue */
		lcd->setColor(0x00, 0x00, 0xff);
	}
	return 0;
}

