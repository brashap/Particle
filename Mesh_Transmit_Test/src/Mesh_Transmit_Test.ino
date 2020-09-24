/*
 * Project Mesh_Transmit_Test
 * Description:
 * Author:
 * Date:
 */
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