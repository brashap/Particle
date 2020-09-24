/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/home/brian/Particle/NycoleMotion/src/NycoleMotion.ino"
/*
 * Project NycoleMotion
 * Description:
 * Author:
 * Date:
 */

void setup();
void loop();
#line 8 "/home/brian/Particle/NycoleMotion/src/NycoleMotion.ino"
void setup() {
  Serial.begin(9600);
  while(!Serial);
  pinMode(A4,INPUT);

}

void loop() {
  Serial.printf("%i, %i \n",millis(), digitalRead(A4));
  delay(500);

}