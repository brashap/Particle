/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#line 1 "/home/brian/Particle/NCD_AdafruitIO/src/NCD_AdafruitIO.ino"
/*
 * Project NCD_AdafruitIO
 * Description: Publish data from NCD Environmental Sensors
 *              to AdafruitIO cloud
 * Author: Brian Rashap
 * Date: 3-Feb-2019
 */

#include <Wire.h>
#include <application.h>
#include <spark_wiring_i2c.h>
#include "Adafruit_CCS811.h"

// Setting up NCD sensors
void setup();
void loop();
void oz();
void mono();
void ccs811();
void sync_my_time();
#line 15 "/home/brian/Particle/NCD_AdafruitIO/src/NCD_AdafruitIO.ino"
#define Addr1 0x50   // Ozone Sensor
#define Addr3 0x52   // CO2 Sensor

Adafruit_CCS811 ccs;

// Setup Adafruit IO MQTT connection 
#include <Adafruit_MQTT.h>

#include "Adafruit_MQTT/Adafruit_MQTT.h" 
#include "Adafruit_MQTT/Adafruit_MQTT_SPARK.h" 
#include "Adafruit_MQTT/Adafruit_MQTT.h" 

/************************* Adafruit.io Setup *********************************/ 
#define AIO_SERVER      "io.adafruit.com" 
#define AIO_SERVERPORT  1883                   // use 8883 for SSL 
#define AIO_USERNAME  "rashap"
#define AIO_KEY       "598169fa3ba94636941a330976e42e2c"

/************ Global State (you don't need to change this!) ***   ***************/ 
TCPClient TheClient; 

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details. 
Adafruit_MQTT_SPARK mqtt(&TheClient,AIO_SERVER,AIO_SERVERPORT,AIO_USERNAME,AIO_KEY); 


/****************************** Feeds ***************************************/ 
// Setup a feed called 'voltage' for publishing. 
// Notice MQTT paths for AIO follow the form: <username>/feeds/<feedname> 

Adafruit_MQTT_Publish Ozone = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/Ozone");
Adafruit_MQTT_Publish CarbonMonoxide = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/CarbonMonoxide");
Adafruit_MQTT_Publish equiv_CO2 = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/equiv_CO2");
Adafruit_MQTT_Publish total_VOC = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/total_VOC");  

float O3;
float CO;
float eCO2;
float tVOC;
float raw_adc;
int sample_freq = 120000; 

void setup() {
     // Set variable   
   Wire.begin();
   Serial.begin(115200); 

  if(!ccs.begin()){
      Serial.println("Failed to start sensor! Please check your wiring.");
   while(1);
  }
   while(!ccs.available());

   delay(100); // pause for Wire and Serial to begin
   Serial.println("\nStarting Up");
   delay(1000);

}

// loop() runs over and over again, as quickly as it can execute.
void loop() {

  Serial.print("\n------------Taking Environmental Measurements-------------\n");

  sync_my_time();
  oz();
  mono();
  ccs811();
  delay(sample_freq);  
}


void oz() {
    unsigned int data[2];

  // Start I2C transmission
  Wire.beginTransmission(Addr1);
  // Select data register
  Wire.write(0x00);
  // Stop I2C transmission
  Wire.endTransmission();

  // Request 2 bytes of data
  Wire.requestFrom(Addr1, 2);

  // Read 2 bytes of data
  // raw_adc msb, raw_adc lsb
  if (Wire.available() == 2)
  {
    data[0] = Wire.read();
    data[1] = Wire.read();
  }

  // Convert the data to 12-bits
  raw_adc = ((data[0] & 0x0F) * 256) + data[1];
  O3 = (1.99 * raw_adc) / 4095.0 + 0.01;

  if( mqtt.Update() ){
       Ozone.publish(O3); 
 } 

  Serial.print("Ozone Concenration (ppm): ");
  Serial.println(O3);
}

void mono()
{
  unsigned int data[2];

  // Start I2C transmission
  Wire.beginTransmission(Addr3);
  // Select data register
  Wire.write(0x00);
  // Stop I2C transmission
  Wire.endTransmission();

  // Request 2 bytes of data
  Wire.requestFrom(Addr3, 2);

  // Read 2 bytes of data
  // raw_adc msb, raw_adc lsb
  if (Wire.available() == 2)
  {
    data[0] = Wire.read();
    data[1] = Wire.read();
  }
  delay(300);

  // Convert the data to 12-bits
  raw_adc = ((data[0] & 0x0F) * 256) + data[1];
  CO = (1000 / 4096.0) * raw_adc + 10;

  if( mqtt.Update() ){
       CarbonMonoxide.publish(CO); 
 } 
  Serial.print("CO Concenration (ppm): ");
  Serial.println(CO);
}

void ccs811() {
  if(ccs.available()){
    eCO2 = ccs.geteCO2();
    tVOC = ccs.getTVOC();
    
    if(!ccs.readData()){
        if( mqtt.Update() ){
          equiv_CO2.publish(eCO2); 
          total_VOC.publish(tVOC);
        } 
      Serial.print("Equivalent CO2 (ppm) : ");
      Serial.println(eCO2);
      Serial.print("Total VOC (ppb): ");
      Serial.println(tVOC);
    }
    else{
      Serial.println("ERROR!");
      while(1);
    }
  }
  else {
    Serial.println("CS811 Not Available");
  }
}

void sync_my_time() {
  Time.zone(-7); // Set Time Zone to Mountain (UTC - 7)
  unsigned long cur = millis();
  
    // Request time synchronization from Particle Device Cloud
    Particle.syncTime();
   
    // Wait until Photon receives time from Particle Device Cloud (or connection to Particle Device Cloud is lost)
    waitUntil(Particle.syncTimeDone);
    // Check if synchronized successfully
    if (Particle.timeSyncedLast() >= cur)
    {
      // Print current time
      Serial.print("The current time (MST) is: ");
      Serial.println(Time.timeStr());
    }
}