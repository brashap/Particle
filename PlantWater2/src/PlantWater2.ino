/*
 * Project PlantWater2
 * Description: Revised IoT Class House Plant Watering System
 * Author: Brian Rashap
 * Date: 3-DEC-2020
 */

#include "Credentials.h"
//#include <JsonParserGeneratorRK.h>
#include <Adafruit_MQTT.h>
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"

// Setup SSD_1306 Display
#define OLED_ADDR   0x3C
#define SSD1306_128_64
Adafruit_SSD1306 display(-1);

// THese #include statement is for MQTT
#include "Adafruit_MQTT/Adafruit_MQTT.h" 
#include "Adafruit_MQTT/Adafruit_MQTT_SPARK.h" 
#include "Adafruit_MQTT/Adafruit_MQTT.h" 

/************ Global State (you don't need to change this!) ***   ***************/ 
TCPClient TheClient; 

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details. 
Adafruit_MQTT_SPARK mqtt(&TheClient,AIO_SERVER,AIO_SERVERPORT,AIO_USERNAME,AIO_KEY); 


/****************************** Feeds ***************************************/ 
// Setup a feed called 'voltage' for publishing. 
// Notice MQTT paths for AIO follow the form: <username>/feeds/<feedname> 

Adafruit_MQTT_Publish Htemp = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/Home_Temperature");
Adafruit_MQTT_Publish Hmoist = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/Home_Moisture");
Adafruit_MQTT_Publish Hwater = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/Home_Water"); 
Adafruit_MQTT_Publish Hpres = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/Home_Pressure"); 
Adafruit_MQTT_Publish Hhum = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/Home_Humidity"); 
Adafruit_MQTT_Publish Hdust = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/Home_Dust"); 

Adafruit_MQTT_Subscribe onoffbutton = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/LED_On"); 

// Declare Constants
const byte BME_ADDR = 0x67;
const byte OLED_ADDR = 0x3C;
const byte BLUEPIN = D9;
const byte YELLOWPIN = D11;
const byte RELAYPIN = D10;
const byte MOISTPIN = A4;
const byte AQPIN = A0;
const byte DUSTPIN = A1;

#define SEALEVELPRESSURE_HPA (1013.25)
Adafruit_BME280 bme; 

/************Declare Variables*************/
int moist;
int soilDelay = 60000;

void setup() {
  Serial.begin(9600);
  delay(100);             //give time for Serial Monitor to initalize

  // Initialize Pins
  pinMode(BLUEPIN,INPUT_PULLDOWN);
  pinMode(YELLOWPIN,INPUT_PULLDOWN);
  pinMode(RELAYPIN,OUTPUT);
  pinMode(MOISTPIN,INPUT);
  pinMode(DUSTPIN,INPUT);
}


void loop() {
  digitalWrite(RELAYPIN,HIGH);
  delay(100);
  digitalWrite(RELAYPIN,LOW);
  delay(100);
}