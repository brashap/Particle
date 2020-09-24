/*
 * Project HelloMorning
 * Description: Test Particle Argon - don't forget to set device parameters
 * Author: Brian Rashap
 * Date: 9-April-2020
 */
#include <Particle.h>

void setup() {
  pinMode(D7,OUTPUT);
}

void loop() {
  digitalWrite(D7,HIGH);
  delay(100);
  digitalWrite(D7,LOW);
  delay(100);
} 