/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "c:/Users/IoT_Instructor/Documents/Particle/StringTest/src/StringTest.ino"
/*
 * Project StringTest
 * Description:
 * Author:
 * Date:
 */

void setup();
void loop();
#line 8 "c:/Users/IoT_Instructor/Documents/Particle/StringTest/src/StringTest.ino"
String name;


// setup() runs once, when the device is first turned on.
void setup() {
  Serial.begin(9600);
  delay(1000);
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  name = "Kaleb";

  Serial.printf("My name is %s \n",name.c_str());

  name = "Thomas";
  Serial.printf("My new name is %s \n",name.c_str());

}