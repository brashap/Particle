/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#line 1 "/home/brian/Particle/AudioTest/src/AudioTest.ino"
/*
 * Project: AudioTest
 * Description: Test Particle ADC
 * Author: Brian Rashap
 * Date: 03-Jan-2019
 */


#include "Particle.h"

void setup();
void loop();
#line 11 "/home/brian/Particle/AudioTest/src/AudioTest.ino"
int analogPin = A1;
int val = 0;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  val = analogRead(A1);
  Serial.print(millis());
  Serial.print("  ----   ");
  Serial.println(val);
  delay(50);
}






/* 
const int sampleWindow = 50; // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;
 
void setup() 
{
   Serial.begin(9600);
}
 
 
void loop() 
{
   unsigned long startMillis= millis();  // Start of sample window
   unsigned int peakToPeak = 0;   // peak-to-peak level
 
   unsigned int signalMax = 0;
   unsigned int signalMin = 1024;
 
   // collect data for 50 mS
   while (millis() - startMillis < sampleWindow)
   {
      sample = analogRead(0);
      if (sample < 1024)  // toss out spurious readings
      {
         if (sample > signalMax)
         {
            signalMax = sample;  // save just the max levels
         }
         else if (sample < signalMin)
         {
            signalMin = sample;  // save just the min levels
         }
      }
   }
   peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude
   double volts = (peakToPeak * 5.0) / 1024;  // convert to volts
 
   Serial.println(volts);
}
*/