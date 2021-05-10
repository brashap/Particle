/*
 * Project AnalogSignal
 * Description:
 * Author:
 * Date:
 */

#include <math.h>
SYSTEM_MODE(SEMI_AUTOMATIC);

const float freq = 10;  // Frequency in Hz
float Vsin, Vout;
int maxFreq;
float t;

void setup() {
  pinMode(A5,OUTPUT);
  maxFreq = analogWriteMaxFrequency(A5);
  //analogWriteResolution(A5,10);
}

void loop() {
  t = micros()/1000000.0;
  Vsin = sin(2*M_PI*freq*t);
  Vout = 128*(Vsin+1);
  analogWrite(A5,127,maxFreq/2);
}