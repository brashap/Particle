/*
 * Project Mesh_Recieve_Test
 * Description:
 * Author:
 * Date:
 */

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