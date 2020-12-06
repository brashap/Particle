/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#line 1 "c:/Users/IoT_Instructor/Documents/Particle/I2C_Scan/src/I2C_Scan.ino"
/*
 * Project I2C_Scan
 * Description: Scan I2C bus and return found addresses
 * Author: Brian Rashap
 * Date: 13-Jan-2020
 */

#include "Particle.h"

void setup();
void loop();
#line 10 "c:/Users/IoT_Instructor/Documents/Particle/I2C_Scan/src/I2C_Scan.ino"
unsigned long delayTime;

void setup()
{
	Wire.begin();
	Serial.begin(9600);
	while(!Serial);    // time to get serial running
	Serial.println("\nI2C Scanner");

	    unsigned status;
    
    // default settings
    // (you can also pass in a Wire library object like &Wire2)
}


void loop()
{
	byte error, address;
	int nDevices;

	Serial.println("Scanning...");
	delay(1000);


	nDevices = 0;
	for(address = 1; address < 127; address++ )
	{
		// The i2c_scanner uses the return value of
		// the Write.endTransmisstion to see if
		// a device did acknowledge to the address.
		Wire.beginTransmission(address);
		error = Wire.endTransmission();

		if (error == 0)
		{
			Serial.print("I2C device found at address 0x");
			if (address<16)
				Serial.print("0");
			Serial.print(address,HEX);
			Serial.println("  !");

			nDevices++;
		}
		else if (error==4)
		{
			Serial.print("Unknow error at address 0x");
			if (address<16)
				Serial.print("0");
			Serial.println(address,HEX);
		}
	}
	if (nDevices == 0)
		Serial.println("No I2C devices found\n");
	else
		Serial.println("done\n");

	delay(5000);           // wait 5 seconds for next scan
}