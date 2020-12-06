/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "c:/Users/IoT_Instructor/Documents/Particle/PlantWater2/src/PlantWater2.ino"
/*
 * Project PlantWater2
 * Description: Revised IoT Class House Plant Watering System
 * Author: Brian Rashap
 * Date: 3-DEC-2020
 */



// Declare Constants
void setup();
void loop();
#line 11 "c:/Users/IoT_Instructor/Documents/Particle/PlantWater2/src/PlantWater2.ino"
const byte BME_ADDR = 0x67;
const byte OLED_ADDR = 0x3C;
const byte BLUEPIN = D9;
const byte YELLOWPIN = D11;
const byte RELAYPIN = D10;


void setup() {
  Serial.begin(9600);
  delay(100);             //give time for Serial Monitor to initalize

  // Initialize Pins
  pinMode(BLUEPIN,INPUT_PULLDOWN);
  pinMode(YELLOWPIN,INPUT_PULLDOWN);
  pinMode(RELAYPIN,OUTPUT);
}


void loop() {
  digitalWrite(RELAYPIN,HIGH);
  delay(100);
  digitalWrite(RELAYPIN,LOW);
  delay(100);
}