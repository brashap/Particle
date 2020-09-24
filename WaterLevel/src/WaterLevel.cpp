/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#line 1 "/home/brian/Particle/WaterLevel/src/WaterLevel.ino"
/*
 * Project WaterLevel
 * Description: Wather Level sensor for flood detection
 * Author: Brian Rashap
 * Date: 18-Jan-2020
 */

#include <Particle.h>

void setup();
void loop();
#line 10 "/home/brian/Particle/WaterLevel/src/WaterLevel.ino"
const int Rref = 560;
float Vlev;
float Rlev;
const int Vref = 4096;
int Lin = A5;
const float Dint = 110;
const float Dslope = 15;
float Depth;
int i;
float n = 3;


// setup() runs once, when the device is first turned on.
void setup() {
  Serial.begin(9600);
  while(!Serial);
  // Put initialization like pinMode and begin functions here.

  pinMode(Lin,INPUT);

}

// loop() runs over and over again, as quickly as it can execute.
void loop() {

  Vlev = 0;
  for (i=0; i<n; i++) {
    Vlev = Vlev + analogRead(Lin);
    delay(5000);
  }
  Vlev = Vlev / n;
  Rlev = ((Vref - Vlev)/ Vlev) * Rref;
  Depth = (Rlev - Dint)/Dslope;

  Serial.print(Time.timeStr());
  Serial.print(": ");
  Serial.print(Vlev); 
  Serial.print("  ");
  Serial.print(Rlev);
  Serial.print("    Depth = ");
  Serial.print(Depth);
  Serial.println(" inches.");


  delay(15000);

  // The core of your code will likely live here.

}