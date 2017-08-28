/*
 * Sensor Cluster using Sensors Mezzaine on DragonBoard410c
 * Author: Radhika Paralkar
 * Copyright (c) 2017 Linaro Ltd.
 * All rights reserved.
 ********************************
 * 
 * A0 --> Light Sensor
 * A1 --> Temperature Sensor
 * A2 --> Sound Sensor
 * D4 --> Touch Sensor Module
 * D5 --> Button
 * D6 --> Rotary Angle Sensor
 */

//Define the pins for each sensor

const int lightSensor = A0;
const int tempSensor = A1;
const int soundSensor = A2;
const int touchSensor = 4;
const int button = 5;
const int rotarySensor = 6;


/*Setup runs only once during the program. Set all sensor pins as 
Input and set the baud rate for serial for printing on the serial port*/

void setup()
{
    Serial.begin(9600);
    pinMode(lightSensor, INPUT);           
    pinMode(tempSensor, INPUT);
    pinMode(soundSensor, INPUT);
    pinMode(touchSensor, INPUT);
    pinMode(button, INPUT);
    pinMode(rotarySensor, INPUT);
}

/* The light, temperature and sound sensors give analog readings, hence 
they have been placed on the analog pins and we use analogRead to read 
their values. Similarly, the button and touch sensor will give digital 
values. The rotary angle sensor would ideally provide analog values, 
however since we have only three analog pins, we connect the rotary angle 
sensor onto a digital pin*/
  
void loop() 
{
  int light_sensorVal = analogRead(lightSensor);
	int temp_sensorVal = analogRead(tempSensor);
	int sound_sensorVal = analogRead(soundSensor);
	int touch_sensorVal = digitalRead(touchSensor);
	int button_val = digitalRead(button);
	int rotary_sensorVal = digitalRead(rotarySensor);

	Serial.println("Sensor      | Value     ");
	Serial.println("--------------------");

	Serial.print("Light       | ");
	Serial.println(light_sensorVal);

	Serial.print("Temperature | ");
	Serial.println(temp_sensorVal);

	Serial.print("Sound       | ");
	Serial.println(sound_sensorVal);

	Serial.print("Touch       | ");
	Serial.println(touch_sensorVal);

	Serial.print("Button      | ");
	Serial.println(button_val);

	Serial.print("Rotary Angle| ");
	Serial.println(rotary_sensorVal);
	delay(400);

	Serial.println("");
}
