/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#line 1 "c:/Users/IoTPa/Documents/Particle/HelloTest/src/HelloTest.ino"
/*
 * Project HelloTest
 * Description:
 * Author:
 * Date:
 */
#include <Particle.h>

void setup();
void loop();
#line 9 "c:/Users/IoTPa/Documents/Particle/HelloTest/src/HelloTest.ino"
void setup() {
  pinMode(D7,OUTPUT);
}

void loop() {
  digitalWrite(D7,HIGH);
  delay(1000);
  digitalWrite(D7,LOW);
  delay(1000);
} 