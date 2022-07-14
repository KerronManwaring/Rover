# by Kerron Manwaring

# Nintendo Wii Nunchuk 
# Arduino Nano
# Xbee 900 RF Module Serial 

#include <Wire.h>
#include "Nunchuk.h"
#include <Math.h>


#define _max  255
#define _min -255
#define threshold 50


bool joystick_released     = false;
bool btn_toggle_c = false;
bool btn_toggle_z = false;
bool accelerometer_released = false;

void setup() {
  Wire.begin();
  Serial.begin(115200);
  Serial.println( "Compiled: " __DATE__ ", " __TIME__ ", " __VERSION__);
  delay(10);
  nunchuk_init();
  Serial.println("Remote Controller On!");
  
  Serial.println("rc:true:"); // Code 
  Serial.println("rc:true:"); // Code 
  Serial.println("rc:true:"); // Code  
   
  Serial.println("joystick:-1,-1:"); // to stop
  Serial.println("joystick:-1,-1:"); // to stop
  Serial.println("joystick:-1,-1:"); // to stop
  
  Serial.println("accel:0,0:");  // to stop
  Serial.println("accel:0,0:");  // to stop
  Serial.println("accel:0,0:");  // to stop
  
  if (!nunchuk_read()) {
    nunchuk_init();
    Serial.println("Chuck initialized");
  }
  delay(100);

}

void loop() {

  if (!nunchuk_read()) {
    nunchuk_init();
    Serial.println("Chuck initialized");
  }
  Buttons();
  joystick();
  delay(50);
}



void joystick() {

  long  x =  map(nunchuk_joystickX(), -100, 100, _max, _min);
  long  y =  map(nunchuk_joystickY(), -100, 100, _max, _min);
  float a = (nunchuk_joystick_angle() * (180 / PI)) + 180;
  long  r = sqrt((x * x) + (y * y));
  
  if (r > threshold) {
    Serial.print("joystick:");
    Serial.print(r);
    Serial.print(",");
    Serial.print(a, 0);
    Serial.println(":");
    joystick_released = true;
  } else {
    r = 0;
    if (joystick_released) {
      joystick_released = false;
      Serial.println("joystick:-1,-1:"); // to stop
      Serial.println("joystick:-1,-1:"); // to stop
      Serial.println("joystick:-1,-1:"); // to stop
    }
  }
}

void Buttons() {
  
  if ((nunchuk_buttonC()) && (nunchuk_buttonZ())) { //Both Pressed
    accelerometer();
    accelerometer_released = true;
  }
  else if (nunchuk_buttonZ()) {                     //Z pressed
    Serial.println("btn:Z:");
  }
  else if (nunchuk_buttonC()) {                     //C pressed
    Serial.println("btn:C:");
  }
  else {                                            //None pressed
    if (accelerometer_released)  {
      accelerometer_released = false;
      Serial.println("accel:0,0:"); // to stop
      Serial.println("accel:0,0:"); // to stop
      Serial.println("accel:0,0:"); // to stop
    }
  }  
}

void accelerometer() {
  Serial.print("accel: ");
  Serial.print(nunchuk_pitch()  * (180 / PI));
  Serial.print(",");
  Serial.print(nunchuk_roll() * (180 / PI));
  Serial.println(":");
}



//void Debug() {
//  Serial.print(nunchuk_joystickX());
//  Serial.print(" , ");
//  Serial.print(nunchuk_joystickY());
//  Serial.print(" | ");
//  Serial.print(nunchuk_joystick_angle() * (180 / PI) + 180);
//  Serial.print(" | ");
//  Serial.print(nunchuk_pitch() * (180 / PI));
//  Serial.print(" , ");
//  Serial.print(nunchuk_roll()  * (180 / PI));
//  Serial.print(" | ");
//  Serial.print(nunchuk_buttonC());
//  Serial.print(" , ");
//  Serial.println(nunchuk_buttonZ());
//}4481851



//void joystickProcess_() {
//  String dir = "";
//  long  x =  map(nunchuk_joystickX(), -100, 100, _max, _min);
//  long  y =  map(nunchuk_joystickY(), -100, 100, _max, _min);
//  float a = (nunchuk_joystick_angle() * (180 / PI)) + 180;
//  long  r = sqrt((x * x) + (y * y));
//
//  if (r > threshold) {
//
//    r =  map(r, threshold + 1 , _max, 0, _max);
//
//    if ((a > 45) && (a < 135)) {
//      dir = "forward";
//    }
//
//    if (((a < 45) && (a >= 0)) || ((a <= 360) && (a > 315))) {
//      dir = "left";
//    }
//
//    if ((a < 315) && (a > 225)) {
//      dir = "back";
//    }
//
//    if ((a > 135 ) && (a < 225)) {
//      dir = "right";
//    }
//
//    Serial.print("joystick:");
//    Serial.println(dir);
//    Serial.print("Speed:");
//    Serial.println(r);
//    joystick_released = true;
//  } else {
//    dir = "";
//    r   = 0;
//    if (joystick_released) {
//      joystick_released = false;
//      Serial.println("joystick:Stop");
//      Serial.print("Speed:0");
//    }
//
//  }
//}




/*
     String dir = "";
  pitch  =  map(pitch, 0, 365, _max, _min);
  roll   =  map(roll,  0, 365, _max, _min);
  //float a = (atan2(pitch, roll) * (180 / 3.14159265359)) + 180 ;
  float a = (atan2(pitch, roll) * (180 / 3.14159265359)) + 180;
  long  r = sqrt((roll * roll) + (pitch * pitch));

  if ((a > 45) && (a < 135)) {
    dir = "forward";
  }

  if (((a < 45) && (a >= 0)) || ((a <= 360) && (a > 315))) {
    dir = "right";
  }

  if ((a < 315) && (a > 225)) {
    dir = "back";
  }

  if ((a > 135 ) && (a < 225)) {
    dir = "left";
  }
*/
