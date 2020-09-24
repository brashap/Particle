/*
 * Project NCD_CCS811
 * Description:
 * Author:
 * Date:
 */

#include <Particle.h>
#include "Adafruit_CCS811.h"

Adafruit_CCS811 ccs;

int data_eCO2;
int data_TVOC;
float dtime;

void setup() {
  
    // Set variable
  Particle.variable("i2cdeviceCCS","CCS811");
  Particle.variable("eCO2",data_eCO2);
  Particle.variable("TVOC",data_TVOC);
  
  
  Serial.begin(9600);
  Serial.println("CCS811 test");

  if(!ccs.begin()){
    Serial.println("Failed to start sensor! Please check your wiring.");
    while(1);
  }
 
  // Wait for the sensor to be ready
  while(!ccs.available());
}

void loop() {
  if(ccs.available()){
    data_eCO2 = ccs.geteCO2();
    data_TVOC = ccs.getTVOC();
    dtime = millis()/60000.0;
    
    Serial.print("Time: ");
    Serial.print(dtime);
    Serial.print(" minutes, ");
    
    if(!ccs.readData()){
      Serial.print("CO2: ");
      Serial.print(data_eCO2);
      Particle.publish("eCO2", String(data_eCO2));
      Serial.print("ppm, TVOC: ");
      Serial.println(data_TVOC);
      Particle.publish("TVOC", String(data_TVOC));
    }
    else{
      Serial.println("ERROR!");
      while(1);
    }
  }
  delay(30000);
}