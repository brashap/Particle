/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "application.h"
#line 1 "/home/brian/Particle/Mesh_Recieve_Test/src/Mesh_Recieve_Test.ino"
/*
 * Project Mesh_Recieve_Test
 * Description:
 * Author:
 * Date:
 */

void setup();
void loop();
#line 8 "/home/brian/Particle/Mesh_Recieve_Test/src/Mesh_Recieve_Test.ino"
int boardLed = D7; // This is the LED that is already on your device.

void setup() {
  // This part is mostly the same:
  pinMode(boardLed,OUTPUT); // Our on-board LED is output as well
  
}


// Now for the loop.

void loop() {
    
        Mesh.publish ("beam", "broken");
        digitalWrite(boardLed,HIGH);
        delay(500);
        digitalWrite(boardLed,LOW);
        Mesh.publish ("beam", "fixed");
        
        delay (5000);
}