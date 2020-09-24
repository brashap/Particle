/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#line 1 "/home/brian/Particle/GY61_Rocket/src/GY61_Rocket.ino"
/*
 * Project GY61_Rocket
 * Description: GY61 Accerometer for Model Rockets
 *              Send Data to Adafruit.IO for testing
 * Author: Brian A. Rashap
 * Date: 11/9/2019
 */

#include <Adafruit_MQTT.h>


#include "Adafruit_MQTT/Adafruit_MQTT.h"
#include "Adafruit_MQTT/Adafruit_MQTT_SPARK.h"

/************************* Adafruit.io Setup *********************************/
#define AIO_SERVER      "io.adafruit.com" 
#define AIO_SERVERPORT  1883                   // use 1883 or 8883 for SSL 
#define AIO_USERNAME  "rashap"
#define AIO_KEY       "598169fa3ba94636941a330976e42e2c"

/************ Global State (you don't need to change this!) ******************/ 
TCPClient TheClient; 

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details. 
Adafruit_MQTT_SPARK mqtt(&TheClient,AIO_SERVER,AIO_SERVERPORT,AIO_USERNAME,AIO_KEY); 

/****************************** Feeds ***************************************/
// Notice MQTT paths for AIO follow the form: <username>/feeds/<feedname> 

Adafruit_MQTT_Publish gy_x = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/GY_X");
Adafruit_MQTT_Publish gy_y = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/GY_Y");
Adafruit_MQTT_Publish gy_z = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/GY_Z");

#include "Particle.h"
void setup();
void loop();
#line 35 "/home/brian/Particle/GY61_Rocket/src/GY61_Rocket.ino"

float x;
double y;
float z;

int xPin = A0;
int yPin = A1;
int zPin = A2;


// setup() runs once, when the device is first turned on.
void setup() {
  // Put initialization like pinMode and begin functions here.
    Serial.begin(115200);
    while(!Serial);         // wait for serial to start running
    Serial.println("Serial Monitor Up and Running");

    pinMode(xPin,INPUT);
    pinMode(yPin,INPUT);
    pinMode(zPin,INPUT);
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  // The core of your code will likely live here.
    x = (analogRead(xPin)-2000.0)/400.0;
    y = (analogRead(yPin)-2000.0)/400.0;
    z = (analogRead(zPin)-2000.0)/400.0 ;

    Serial.println("----------------Data to Publish-----------------");
    Serial.print("X-Axis Acceleration ");
    Serial.print(x);
    Serial.println(" G");
    Serial.print("Y-Axis Acceleration ");
    Serial.print(y);
    Serial.println(" G");
    Serial.print("Z-Axis Acceleration ");
    Serial.print(z);
    Serial.println(" G");
    Serial.println("------------------End Publish-------------------");


if(mqtt.Update()) {
    gy_x.publish(x);
    gy_y.publish(y);
    gy_z.publish(z);
    }   

delay(10000);

}