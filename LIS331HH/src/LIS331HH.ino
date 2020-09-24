/*
 * Project LIS331HH
 * Description: NCD 6-axis motion detector
 * Author: Brian Rashap
 * Date: 22-APR-2020
 */

#include <math.h>
// LIS331HH I2C address is 0x18(24)
#define Addr 0x18

byte data[6];

int xAccl = 0;
int yAccl =  0;
int zAccl = 0;

float xG;
float yG;
float zG;
float tG;

void setup()
{

  Wire.begin();
  Serial.begin(9600);

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select control register 1
  Wire.write(0x20);
  // Enable X, Y, Z axis, power on mode, data rate selection = 50Hz
  Wire.write(0x27);
  // Stop I2C Transmission
  Wire.endTransmission();

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select control register 4
  Wire.write(0x23);
  // Set Continuos update, +/- 6g, self-test enabled
  Wire.write(0x00);
  // Stop I2C Transmission
  Wire.endTransmission();
  delay(300);
}

void loop()
{
  for (int i = 0; i < 6; i++)
  {
    // Start I2C Transmission, Select data register, Stop I2C Transmission
    Wire.beginTransmission(Addr);
    Wire.write((40 + i));
    Wire.endTransmission();

    // Request 1 byte of data
    Wire.requestFrom(Addr, 1);

    // Read 6 bytes of data
    // xAccl lsb, xAccl msb, yAccl lsb, yAccl msb, zAccl lsb, zAccl msb
    if (Wire.available() == 1)
    {
      data[i] = Wire.read();
    }
    delay(300);
  }

  // Convert the data
  xAccl = ((data[1] * 256) + data[0]);
  if (xAccl > 32767)
  {
    xAccl -= 65536;
  }

  yAccl = ((data[3] * 256) + data[2]);
  if (yAccl > 32767)
  {
    yAccl -= 65536;
  }

  zAccl = ((data[5] * 256) + data[4]);
  if (zAccl > 32767)
  {
    zAccl -= 65536;
  }

  // Convert to G's (Gravity = 1G = 9.8m/s^2)
  xG = xAccl/5250.0;
  yG = yAccl/5250.0;
  zG = zAccl/5250.0;

  tG = sqrt(pow(xG,2)+pow(yG,2)+pow(zG,2));
  
  // Output data to dashboard
  Serial.printf("-----------Acceleration---------------\n");
  Serial.printf("Acceleration in X-Axis: %0.2f \n", xG);
  Serial.printf("Acceleration in Y-Axis: %0.2f \n", yG);
  Serial.printf("Acceleration in Z-Axis: %0.2f \n", zG);
  Serial.printf("Total Acceleration: %0.2f \n", tG);
  delay(250);
}