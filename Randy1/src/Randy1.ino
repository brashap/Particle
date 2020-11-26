/*
 * Project Randy1
 * Description: Demonstration Code for JSON Payloads  
 * Author: Brian Rashap
 * Date:  25-OCT-2020
 */

#include <JsonParserGeneratorRK.h>

const int PayloadFreq = 30000;  

// Declare variables
int pulse;
int sleeping_rr; //respitory rate
int abg; //arterial blood gases
bool snoring;
bool awake;

unsigned int currentTime;
unsigned int lastPayloadTime;

void setup() {
  lastPayloadTime = -99999;

}

void loop() {
  currentTime = millis();

  //run at frequency set in PayloadFreq variable
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