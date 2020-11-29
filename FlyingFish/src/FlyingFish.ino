/*
 * Project FlyingFish
 * Description: Demo code to determine Rs of Flying Fish MQ9 sensor
 * Author: Brian Rashap
 * Date: 3-SEP-2020
 */

#include <math.h>

const int MQ9 = A0;
const int Rl = 1000;
const float Vs = 5.0;
int i;
int Rs;
int R1;
float RsRo;
int rawADC;
float Vin;
float ppmCO;

void setup() {
  Serial.begin(9600);
  pinMode(MQ9,INPUT);
  Rs = getRs();
  R1 = 830;
}

void loop() {
  Vin = analogRead(MQ9)*(3.3/4096);
  RsRo = (Vs/Vin-1)*(Rl/R1);
  ppmCO = 595*pow(RsRo,-2.24);
  Serial.printf("RsRo = %02f, ppmCO = %02f \n",RsRo,ppmCO);
  delay(5000);
}

int getRs() {
  int i;
  int Rs;
  int rawADC;
  float Vin;

  rawADC = 0;
  for(i=0;i<100;i++) {
    rawADC += analogRead(MQ9);
    delay(20);
  }
  rawADC = rawADC / 100;
  Vin = rawADC*(3.3/4096);
  Rs = ((Vs/Vin)-1)*Rl;
  Serial.printf("Raw Input = %i, Vin = %0.2f, Rs = %i. \n", rawADC, Vin, Rs);
  return Rs;
}