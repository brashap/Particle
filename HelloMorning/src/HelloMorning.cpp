/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#line 1 "c:/Users/IoTPa/Documents/Particle/HelloMorning/src/HelloMorning.ino"
/*
 * Project HelloMorning
 * Description:
 * Author:
 * Date:
 */
#include <Particle.h>

void setup();
void loop();
#line 9 "c:/Users/IoTPa/Documents/Particle/HelloMorning/src/HelloMorning.ino"
void setup() {
  pinMode(D7,OUTPUT);
}

void loop() {
  digitalWrite(D7,HIGH);
  delay(100);
  digitalWrite(D7,LOW);
  delay(100);
} 