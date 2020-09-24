/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "c:/Users/IoTPa/Documents/Particle/HelloParticle/src/HelloParticle.ino"
/*
 * Project HelloParticle
 * Description:
 * Author:
 * Date:
 */

// setup() runs once, when the device is first turned on.
void setup();
void loop();
#line 9 "c:/Users/IoTPa/Documents/Particle/HelloParticle/src/HelloParticle.ino"
void setup() {
pinMode(D7,OUTPUT);
}
void loop() {
digitalWrite(D7,HIGH);
delay(1000);
digitalWrite(D7,LOW);
delay(1000);
}