/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "c:/Users/IoT_Instructor/Documents/Particle/hello/src/hello.ino"
/*
 * Project hello
 * Description:
 * Author:
 * Date:
 */

void setup();
void loop();
#line 8 "c:/Users/IoT_Instructor/Documents/Particle/hello/src/hello.ino"
void setup() {
  Serial.begin();
  pinMode(D7,OUTPUT);
}

void loop() {
  Serial.printf("Random Number: %i \n ",random(0,43));
  digitalWrite(D7,HIGH);
  delay(1000);
  digitalWrite(D7,LOW);
  delay(1000);
}