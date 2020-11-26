/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "c:/Users/IoTPa/Documents/Particle/Randy1/src/Randy1.ino"
/*
 * Project Randy1
 * Description: Demonstration Code for JSON Payloads  
 * Author: Brian Rashap
 * Date:  25-OCT-2020
 */

#include <JsonParserGeneratorRK.h>

void setup();
void loop();
void createEventPayLoad(int _pulse, int _rr, int _abg, bool _sn, bool _awake);
#line 10 "c:/Users/IoTPa/Documents/Particle/Randy1/src/Randy1.ino"
const int PayloadFreq = 30000;  

// Declare variables
int pulse;
int sleeping_rr; //respitory rate
int abg; //arterial blood gases
bool snoring;
bool awake;

unsigned int currentTime;
unsigned int lastPayloadTime;

// setup() runs once, when the device is first turned on.
void setup() {
  lastPayloadTime = -99999;

}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  currentTime = millis();

  //run once per second
  if((currentTime-lastPayloadTime)>PayloadFreq) {
    
    // Create some fake data
    pulse = random(42,90);
    sleeping_rr = random(10,25);
    abg = random(90,102);
    snoring = random(0,2);
    awake = random(0,42)/40;

    createEventPayLoad(pulse,sleeping_rr,abg,snoring,awake);
    lastPayloadTime = millis();
  }  

}


void createEventPayLoad(int _pulse, int _rr, int _abg, bool _sn, bool _awake) {
  JsonWriterStatic<256> jw;
  {
    JsonWriterAutoObject obj(&jw);

    jw.insertKeyValue("Pulse", _pulse);
    jw.insertKeyValue("Respitory_Rate", _rr);
    jw.insertKeyValue("Blood_02", _abg);
    jw.insertKeyValue("Snoring", _sn);
    jw.insertKeyValue("Awake", _awake);
  }
  Particle.publish("sleep_data",jw.getBuffer(), PRIVATE);
}