/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#line 1 "c:/Users/IoT_Instructor/Documents/Particle/HelloWorld/src/HelloWorld.ino"
/*
 * Project HelloWorld
 * Description: Test Program
 * Author: Brian Rashap
 * Date: 5-APR-2020
 */

#include <Particle.h>
#include <dct.h>

void setup();
void loop();
#line 11 "c:/Users/IoT_Instructor/Documents/Particle/HelloWorld/src/HelloWorld.ino"
bool onoff;
//SYSTEM_MODE(SEMI_AUTOMATIC);

// setup() runs once, when the device is first turned on.
void setup() {
  // to flip listening mode bit
  // const uint8_t val = 0x01;
  // dct_write_app_data(&val, DCT_SETUP_DONE_OFFSET, 1);
  
  Serial.begin();
  delay(500);

  pinMode(D7,OUTPUT);
  pinMode(A0,INPUT);
  pinMode(D4,OUTPUT);

  analogWriteResolution(D4,10);     // 2 to 31, default = 8
  // Put initialization like pinMode and begin functions here.


  delay(1000);
  //WiFi.connect();
  delay(10000);
  //Particle.connect();

}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  digitalWrite(D7,HIGH);
  delay(250);
  digitalWrite(D7,LOW);
  delay(500); 

  onoff = analogRead(A0);
  Serial.println(onoff);

  analogWrite(D4,onoff);

  for(int i=0;i<1024;i++) {
    analogWrite(D4,i);
    delay(10);
    Serial.println(i);
    
  }
  Serial.printf("AWF = %i \n",analogWriteMaxFrequency(A0));

  // The core of your code will likely live here.

}