/*  ********************************************* 
 *  SparkFun_MAG3110_Calibrated
 *  Triple Axis Magnetometer Breakout - MAG3110 
 *  Hook Up Guide Example 
 *  
 *  Utilizing Sparkfun's MAG3110 Library
 *  This allows you to see the magnitude of
 *  magnetic fields around the sensor
 *  
 *  You can see interference from power electronics
 *  IE: a microwave
 *  Or put a fridge magnet nearby to see the spikes.
 *  
 *  Use Tools->Serial Plotter to visualize the data
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

  mag.initialize(); //Initialize the MAG3110
}

void loop() {

  int x, y, z;

  if(!mag.isCalibrated()) //If we're not calibrated
  {
    if(!mag.isCalibrating()) //And we're not currently calibrating
    {
      Serial.println("Entering calibration mode");
      mag.enterCalMode(); //This sets the output data rate to the highest possible and puts the mag sensor in active mode
    }
    else
    {
      //Must call every loop while calibrating to collect calibration data
      //This will automatically exit calibration
      //You can terminate calibration early by calling mag.exitCalMode();
      mag.calibrate(); 
    }
  }
  else //We are calibrated
  {
    mag.readMag(&x, &y, &z);
    float magnitude = sqrt(pow(x*mag.x_scale, 2) + pow(y*mag.y_scale, 2)); //x_scale and y_scale are set by calibration! Do not modify them!
    Serial.println(magnitude);
  }
  delay(20);
}
