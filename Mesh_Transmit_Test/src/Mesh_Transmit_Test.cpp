/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "application.h"
#line 1 "/home/brian/Particle/Mesh_Transmit_Test/src/Mesh_Transmit_Test.ino"
/*
 * Project Mesh_Transmit_Test
 * Description:
 * Author:
 * Date:
 */
void beamAction(const char *event, const char *data);
void setup();
void loop();
#line 7 "/home/brian/Particle/Mesh_Transmit_Test/src/Mesh_Transmit_Test.ino"
int led1 = D7; // Instead of writing D0 over and over again, we'll write led1

void beamAction(const char *event, const char *data) {
    
   if (strcmp (data, "broken")==0) { digitalWrite (led1, HIGH);}
   if (strcmp (data, "fixed")==0) { digitalWrite (led1, LOW);}
    
    
    Serial.println (data);
}

 
void setup() {

  pinMode(led1, OUTPUT);
  Serial.begin(); 
  Mesh.subscribe ("beam", beamAction);
  
}


void loop() {

  // Wait 1 second...
  delay(1000);

}