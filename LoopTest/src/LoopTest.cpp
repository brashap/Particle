/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "c:/Users/IoT_Instructor/Documents/Particle/LoopTest/src/LoopTest.ino"
/*
 * Project LoopTest
 * Description: Test the time required to collect Accelerometer data
 * Author: Brian Rashap
 * Date: 17-AUG-2020
 */

//SYSTEM_THREAD(ENABLED);
#include <math.h>
#include "Wire.h" // This library allows you to communicate with I2C devices.
void setup();
void loop();
void getAcc();
#line 11 "c:/Users/IoT_Instructor/Documents/Particle/LoopTest/src/LoopTest.ino"
const int MPU_ADDR = 0x68; // I2C address of the MPU-6050. If AD0 pin is set to HIGH, the I2C address will be 0x69.
int16_t accel_x, accel_y, accel_z; // variables for accelerometer raw data
float xscale = 15700;
float yscale = 16100;
float zscale = 18200;
float Ax,Ay,Az;
float pitch, roll;
int16_t gyro_x, gyro_y, gyro_z; // variables for gyro raw data
int16_t temperature; // variables for temperature data
unsigned long startTime, stopTime, lastTime, sinceLastTime, startTimer;
int i;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR); // Begins a transmission to the I2C slave (GY-521 board)
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0); // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  lastTime = 0;
  startTimer = millis();
  i=0;
  Serial.printf("Starting in 5 seconds\n");
  delay(5000);
}
void loop() {
  if ((millis() - startTimer) > 5000) {
    Serial.printf("Total Iterations %i \n",i);
    delay(5000);
    i=0;
    startTimer=millis();
    lastTime = micros();
  }
  i++;
  while ((micros() - lastTime) < 10000) {}
  sinceLastTime = micros()-lastTime;
  lastTime = micros();
  startTime = micros();
  getAcc();
  stopTime = micros();
  if(sinceLastTime>15000){
    Serial.printf("Loop Time %i for internation %i \n",sinceLastTime,i);
  }

  pitch = asin(Ax) * (360 / (2 * 3.14));
  roll = -atan2(Ay,sqrt(pow(Ax,2)+pow(Az,2))) * (360 / (2 * 3.14));
}

void getAcc() {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H) [MPU-6000 and MPU-6050 Register Map and Descriptions Revision 4.2, p.40]
  Wire.endTransmission(false); // the parameter indicates that the Arduino will send a restart. As a result, the connection is kept active.
  Wire.requestFrom(MPU_ADDR, 7*2, true); // request a total of 7*2=14 registers
  
  // "Wire.read()<<8 | Wire.read();" means two registers are read and stored in the same variable
  accel_x = Wire.read()<<8 | Wire.read(); // reading registers: 0x3B (ACCEL_XOUT_H) and 0x3C (ACCEL_XOUT_L)
  accel_y = Wire.read()<<8 | Wire.read(); // reading registers: 0x3D (ACCEL_YOUT_H) and 0x3E (ACCEL_YOUT_L)
  accel_z = Wire.read()<<8 | Wire.read(); // reading registers: 0x3F (ACCEL_ZOUT_H) and 0x40 (ACCEL_ZOUT_L)

  Ax = accel_x /xscale; //*9.8067;
  Ay = accel_y /yscale; //9.8067;
  Az = accel_z /zscale; //9.8067;

  temperature = Wire.read()<<8 | Wire.read(); // reading registers: 0x41 (TEMP_OUT_H) and 0x42 (TEMP_OUT_L)
  gyro_x = Wire.read()<<8 | Wire.read(); // reading registers: 0x43 (GYRO_XOUT_H) and 0x44 (GYRO_XOUT_L)
  gyro_y = Wire.read()<<8 | Wire.read(); // reading registers: 0x45 (GYRO_YOUT_H) and 0x46 (GYRO_YOUT_L)
  gyro_z = Wire.read()<<8 | Wire.read(); // reading registers: 0x47 (GYRO_ZOUT_H) and 0x48 (GYRO_ZOUT_L)
}