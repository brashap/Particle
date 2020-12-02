/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "c:/Users/IoT_Instructor/Documents/Particle/CharAsciiTest/src/CharAsciiTest.ino"
/*
 * Project CharAsciiTest
 * Description:
 * Author:
 * Date:
 */

void setup();
#line 8 "c:/Users/IoT_Instructor/Documents/Particle/CharAsciiTest/src/CharAsciiTest.ino"
const int degree = 0xB0;
float temp = 98.6;

void setup() {
  Serial.begin(9600);
  delay(1000);
  Serial.printf("My temperature is %0.1f %c",temp,degree);
}