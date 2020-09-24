/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/home/brian/Particle/TMG39931/src/TMG39931.ino"
/*
 * Project TMG39931
 * Description: NCD Gesture, Light, Color module 
 * Author: Brian Rashap
 * Date: 22-APR-2020
 */


// TMG39931 I2C address is 0x39(57)
void setup();
void loop();
void tmgInit();
#line 10 "/home/brian/Particle/TMG39931/src/TMG39931.ino"
#define Addr 0x39
  
void setup()
{
  Wire.begin();
  Serial.begin(9600);
  delay(500);
  tmgInit();
  delay(1000);
}

void loop()
{
  unsigned int data[9];
  
  // Start I2C Transmission, Select Data Register, Stop I2C Transmission
  Wire.beginTransmission(Addr);
  Wire.write(0x94);
  Wire.endTransmission();
  
  // Request 9 bytes of data
  Wire.requestFrom(Addr, 9);
   
  // Read the 9 bytes of data
  // cData channel LSB, cData channel MSB, Red channel LSB, Red channel MSB
  // Green channel LSB, Green channel MSB, Blue channel LSB, Blue channel MSB, proximity
  if(Wire.available() == 9) 
  {
    data[0] = Wire.read();
    data[1] = Wire.read();
    data[2] = Wire.read();
    data[3] = Wire.read();
    data[4] = Wire.read();
    data[5] = Wire.read();
    data[6] = Wire.read();
    data[7] = Wire.read();
    data[8] = Wire.read();
   }
   
  // Convert the data
  float cData = data[1] * 256.0 + data[0];
  float red = data[3] * 256.0 + data[2];
  float green = data[5] * 256.0 + data[4];
  float blue = data[7] * 256.0 + data[6];
  
  // Output data to serial monitor       
  Serial.print("Green Color Luminance : ");
  Serial.println(green);
  Serial.print("Red Color Luminance : ");
  Serial.println(red)  ;
  Serial.print("Blue Color Luminance : ");
  Serial.println(blue) ;
  Serial.print("InfraRed Luminance : ");
  Serial.println(cData) ;
  Serial.print("Proximity of the device : ");
  Serial.println(data[8]);
  delay(5000);
}

void tmgInit() {
  Serial.println("Initializing TMG3993");
  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select Enable register
  Wire.write(0x80);
  // Power ON, ALS enable, Proximity enable, Wait enable
  Wire.write(0x0F);
  // Stop I2C transmission
  Wire.endTransmission();

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select ADC integration time register
  Wire.write(0x81);
  // ATIME : 712ms, Max count = 65535 cycles
  Wire.write(0x00);
  // Stop I2C transmission
  Wire.endTransmission();

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select Wait time register
  Wire.write(0x83);
  // WTIME : 2.78ms
  Wire.write(0xFF);
  // Stop I2C transmission
  Wire.endTransmission();

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select control register
  Wire.write(0x8F);
  // AGAIN is 1x
  Wire.write(0x00);
  // Stop I2C transmission
  Wire.endTransmission();
}