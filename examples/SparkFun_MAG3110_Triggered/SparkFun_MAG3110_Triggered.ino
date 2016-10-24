/*  ********************************************* 
 *  SparkFun_MAG3110_Triggered
 *  Triple Axis Magnetometer Breakout - MAG3110 
 *  Hook Up Guide Example 
 *  
 *  Utilizing Sparkfun's MAG3110 Library
 *  A sketch showing how to use triggered
 *  (one-shot) readings on the MAG3110
 *  
 *  This saves power but may affect the accuracy of the data
 *  See the datasheet for more information
 *  
 *  George B. on behalf of SparkFun Electronics
 *  Created: Sep 22, 2016
 *  Updated: n/a
 *  
 *  Development Environment Specifics:
 *  Arduino 1.6.7
 *  
 *  Hardware Specifications:
 *  SparkFun MAG3110
 *  Bi-directional Logic Level Converter
 *  Arduino Micro
 *  
 *  This code is beerware; if you see me (or any other SparkFun employee) at the
 *  local, and you've found our code helpful, please buy us a round!
 *  Distributed as-is; no warranty is given.
 *  *********************************************/

#include <SparkFun_MAG3110.h>

MAG3110 mag = MAG3110(); //Instantiate MAG3110

void setup() {
  Serial.begin(9600);

  mag.initialize(); //Initializes the mag sensor
  //When initialized, the sensor will be in standby
}

int timeStamp = 0;
void loop() {

  //Trigger a measurement every 2 seconds
  if(millis() - timeStamp > 2000)
  {
    timeStamp = millis();
    mag.triggerMeasurement();
  }
  
  int x, y, z;
  //Only read data when it's ready
  if(mag.dataReady()) {
    //Read the data
    mag.readMag(&x, &y, &z);
  
    Serial.print("X: ");
    Serial.print(x);
    Serial.print(", Y: ");
    Serial.print(y);
    Serial.print(", Z: ");
    Serial.println(z);
  
    Serial.println("--------");
  }
}
