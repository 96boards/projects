// facetrack_servo - Arduino code for servo tracking
// Author - Manivannan Sadhasivam

#include <Servo.h>

#define  ServoX_Max   180   // Maximum X axis tilt (degrees)
#define  ServoY_Max   180   // Maximum Y axis pan (degrees)
#define  ScreenX_Max   320  // Maximum X axis screen resolution
#define  ScreenY_Max   240  // Maximum Y axis screen resolution
#define  ServoX_Pos   90    // Default X axis position of servo (degrees)
#define  ServoY_Pos   120   // Default Y axis position of servo (degrees)
#define  ServoX_Pin   9     // Servo Pin for X axis control
#define  ServoY_Pin   10    // Servo pin for Y axis control
#define  baudrate 9600      // Serial baudrate
#define  ServoX_Steps 1     // Step value X axis
#define  ServoY_Steps 1     // Step value Y axis

int valx = 0;       
int valy = 0;       
int posx = 0;
int posy = 0;
int incx = 10;  	    // Webcam position increment for X axis
int incy = 10;              // Webcam position increment for Y axis

Servo servox;	            //  Servo objects
Servo servoy;

short msb = 0;  
short lsb = 0;  
int position = 0;  

void setup() {

  Serial.begin(baudrate);        // Establish serial connection

  servox.attach(ServoX_Pin); 
  servoy.attach(ServoY_Pin); 

  // Place servos in default position 
  servox.write(ServoX_Pos); 
  delay(200);
  servoy.write(ServoY_Pos); 
  delay(200);
}

void loop () {

  while(Serial.available() <=0); // wait for incoming serial data
  if (Serial.available() >= 4)  // wait for 4 bytes. 
  {
    // Get X axis 2-byte integer from serial
    msb = Serial.read();
    delay(5);
    lsb = Serial.read();
    position = word(msb, lsb);
    valx = position; 
    delay(5);

    // Get Y axis 2-byte integer from serial
    msb = Serial.read();
    delay(5);
    lsb = Serial.read();
    position = word(msb, lsb);
    valy = position; 
    delay(5);

    // Read last servos positions
    posx = servox.read(); 
    posy = servoy.read();

    // Find out if the X component of the face is to the left of the middle of the screen.
    if (valx < (ScreenX_Max/2 - incx)){
      if (posx >= incx ) 
        posx += ServoX_Steps; // Update the pan position variable to move the servo to the left.
    }
    // Find out if the X component of the face is to the right of the middle of the screen.
    else if (valx > ScreenX_Max/2 + incx){
      if (posx <= ServoX_Max-incx) 
        posx -= ServoX_Steps; // Update the pan position variable to move the servo to the right.
    }

    // Find out if the Y component of the face is below the middle of the screen.
    if (valy < (ScreenY_Max/2 - incy)){
      if (posy >= 5)
        posy -= ServoY_Steps; // If it is below the middle of the screen, update the tilt position variable to lower the tilt servo.
    }

    // Find out if the Y component of the face is above the middle of the screen.
    else if (valy > (ScreenY_Max/2 + incy)){
      if (posy <= 175)
      posy += ServoY_Steps; // Update the tilt position variable to raise the tilt servo.
    }

    // Move servos according to the position of face
    servox.write(posx);
    servoy.write(posy);

  }   
}














