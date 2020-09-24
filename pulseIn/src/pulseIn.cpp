/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/home/brian/Particle/pulseIn/src/pulseIn.ino"
/*
 * Project pulseIn
 * Description: Experiment with pulseIn
 * Author: Brian Rashap
 * Date: 21-APR-2020
 */

void setup();
void loop();
#line 8 "/home/brian/Particle/pulseIn/src/pulseIn.ino"
int buttonPin = D8;
unsigned int duration;

void setup() {
  Serial.begin();
  while(!Serial);
  pinMode(buttonPin,INPUT);
    Serial.println("Begin");
}

void loop() {

  duration = pulseIn(buttonPin,HIGH);
  if (duration>0){
    Serial.printf("The low duration was %i \n",duration);
     Serial.println("Begin");
  }
}