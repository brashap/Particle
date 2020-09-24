/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/home/brian/Particle/SEEED_AQ/src/SEEED_AQ.ino"
/*
 * Project SEEED_AQ
 * Description:
 * Author:
 * Date:
 */
#include <Air_Quality_Sensor.h>
#include <Adafruit_BME280.h>

void setup();
void loop();
void getDustSensorReadings();
String getAirQuality();
int getBMEValues(int &temp, int &pressure, int &humidity);
#line 10 "/home/brian/Particle/SEEED_AQ/src/SEEED_AQ.ino"
Adafruit_BME280 bme;

#define DUST_SENSOR_PIN D4
#define SENSOR_READING_INTERVAL 15000

#define AQS_PIN A2
AirQualitySensor aqSensor(AQS_PIN);

unsigned long lastInterval;
unsigned long lowpulseoccupancy = 0;
unsigned long last_lpo = 0;
unsigned long duration;

float ratio = 0;
float concentration = 0;

int temp; 
int pressure;
int humidity;


void setup() {
  Serial.begin(9600);

  pinMode(DUST_SENSOR_PIN, INPUT);
  lastInterval = millis();

  if (aqSensor.init())
    {
      Serial.println("Air Quality Sensor ready.");
    }
    else {
      Serial.println("Air Quality Sensor ERROR!");
    }
  /*
  if (bme.begin()) {
    Serial.println("BME280 Sensor ready.");
    }
    else {
      Serial.println("BME280 Sensor ERROR!");
    }
  */
}


void loop() {
  duration = pulseIn(DUST_SENSOR_PIN, LOW);
  lowpulseoccupancy = lowpulseoccupancy + duration;

  if ((millis() - lastInterval) > SENSOR_READING_INTERVAL) {
    getDustSensorReadings();

    lowpulseoccupancy = 0;
    lastInterval = millis();
    
    String quality = getAirQuality();
    Serial.printlnf("Air Quality: %s", quality.c_str());

    /*
    getBMEValues(temp, pressure, humidity);
    Serial.printlnf("Temp: %d", temp);
    Serial.printlnf("Pressure: %d", pressure);
    Serial.printlnf("Humidity: %d", humidity);
    */
  }
}


void getDustSensorReadings() {

if (lowpulseoccupancy == 0)
{
 lowpulseoccupancy = last_lpo;
}
else
{
 last_lpo = lowpulseoccupancy;
}

ratio = lowpulseoccupancy / (SENSOR_READING_INTERVAL * 10.0);
concentration = 1.1 * (ratio*ratio*ratio) - 3.8 * (ratio*ratio) + 520 * ratio + 0.62;

Serial.printlnf("LPO: %d", lowpulseoccupancy);
Serial.printlnf("Ratio: %f%%", ratio);
Serial.printlnf("Concentration: %f pcs/L", concentration);
}

String getAirQuality()
{
 int quality = aqSensor.slope();
 Serial.println(aqSensor.getValue());
 String qual = "None";

 if (quality == AirQualitySensor::FORCE_SIGNAL)
 {
   qual = "Danger";
 }
 else if (quality == AirQualitySensor::HIGH_POLLUTION)
 {
   qual = "High Pollution";
 }
 else if (quality == AirQualitySensor::LOW_POLLUTION)
 {
   qual = "Low Pollution";
 }
 else if (quality == AirQualitySensor::FRESH_AIR)
 {
   qual = "Fresh Air";
 }

 return qual;
}

int getBMEValues(int &temp, int &pressure, int &humidity)
{
 temp = (int)bme.readTemperature();
 pressure = (int)(bme.readPressure() / 100.0F);
 humidity = (int)bme.readHumidity();

 return 1;
}