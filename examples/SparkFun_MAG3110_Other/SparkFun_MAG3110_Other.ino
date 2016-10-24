/*  ********************************************* 
 *  SparkFun_MAG3110_Other
 *  Triple Axis Magnetometer Breakout - MAG3110 
 *  Hook Up Guide Example 
 *  
 *  Utilizing Sparkfun's MAG3110 Library
 *  
 *  This sketch shows you some of the library's
 *  more obscure functionality
 *  
 *  Read the comments to learn more
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

  mag.initialize();
  //This line makes the output data rate a lot slower
  //Output Data Rate = 1.25Hz
  //Oversampling Ratio = 32
  //This means it takes 32 samples and averages the results
  if(!mag.error) //You can use this to check if there was an error during initialization.
  {
    mag.setDR_OS(MAG3110_DR_OS_1_25_32);
    mag.start();
  }

  //You can set your own offsets without calibration
  //mag.setOffset(MAG3110_X_AXIS, -100);
  //mag.setOffset(MAG3110_Y_AXIS, 300);
  //mag.setOffset(MAG3110_Z_AXIS, -300);

  //You can read the sensor's offset by calling:
  //int offset = mag.readOffset(MAG3110_X_AXIS);

  //You can obtain system information by calling any of the following:
  //mag.isActive(); //Tells you whether the mag sensor is active or in standby
  //mag.isRaw(); //Tells you if the mag sensor is outputting raw data or not
  //mag.isCalibrated(); //Tells you if the mag sensor has been calibrated
  //mag.isCalibrating(); //Tells you if the mag sensor is currently being calibrated
  //uint8_t mode = mag.getSysMode(); //Reads the SYSMOD register. See the datasheet for more information

  //This will reset the sensor to default values
  //It sets the offsets to 0, flags it as uncalibrated, and sets the device to standby mode
  //The Output Data Rate and Oversampling ratio will also be set to 80 and 16 respectively (see datasheet)
  //mag.reset();

  //This will disable the use of user offsets
  //User offsets are enabled by default but are initialized to 0
  //mag.rawData(true);
}

void loop() {

  float xf, yf, zf;
  //Only read data when it's ready
  if(mag.error)
    Serial.println("Could not connect to MAG3110 Sensor!");
  if(mag.dataReady()) {
    mag.readMicroTeslas(&xf, &yf, &zf); //This divides the values by 10 to get the reading in microTeslas
  
    Serial.print("X: ");
    Serial.print(xf);
    Serial.print(", Y: ");
    Serial.print(yf);
    Serial.print(", Z: ");
    Serial.println(zf);
  
    Serial.println("--------");
  }
}
