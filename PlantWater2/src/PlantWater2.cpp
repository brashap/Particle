/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "c:/Users/IoT_Instructor/Documents/Particle/PlantWater2/src/PlantWater2.ino"
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
#include "Adafruit_BME280.h"

// Setup SSD_1306 Display
void setup();
void loop();
void printhello();
void oledprint(float Otemp, float Opres, float Ohum, float Odust, int Omoist);
float getDust();
#line 16 "c:/Users/IoT_Instructor/Documents/Particle/PlantWater2/src/PlantWater2.ino"
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
const byte BME_ADDR = 0x76;
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
bool status;

void setup() {
  Serial.begin(9600);
  delay(100);             //give time for Serial Monitor to initalize

  // initialize and clear display
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();
  display.display();
  printhello();

  // Initialize Pins
  pinMode(BLUEPIN,INPUT_PULLDOWN);
  pinMode(YELLOWPIN,INPUT_PULLDOWN);
  pinMode(RELAYPIN,OUTPUT);
  pinMode(MOISTPIN,INPUT);
  pinMode(DUSTPIN,INPUT);
  pinMode(D7,OUTPUT);

  status = bme.begin(BME_ADDR);
  if (!status) {
    Serial.printf("Error Initializing BME280");
  }
}


void loop() {
  digitalWrite(RELAYPIN,HIGH);
  digitalWrite(D7,HIGH);
  delay(5000);
  digitalWrite(RELAYPIN,LOW);
  digitalWrite(D7,LOW);
  delay(5000);
}


void printhello() {
  display.clearDisplay();
  // display a pixel in each corner of the screen
  display.drawPixel(0, 0, WHITE);
  display.drawPixel(127, 0, WHITE);
  display.drawPixel(0, 63, WHITE);
  display.drawPixel(127, 63, WHITE);
  // display a line of text
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.print("   Hello\n   World!");
  display.display();
}

void oledprint(float Otemp, float Opres, float Ohum, float Odust, int Omoist) {

   // initialize and clear display
  display.clearDisplay();
  display.display();

  // display a pixel in each corner of the screen
  display.drawPixel(0, 0, WHITE);
  display.drawPixel(127, 0, WHITE);
  display.drawPixel(0, 63, WHITE);
  display.drawPixel(127, 63, WHITE);

  // display a line of text
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,5);
  display.printf("Environmental Reading");
  display.setCursor(0,18);
  display.printf("Temperature(F) %0.2f\n",Otemp);
  display.printf("Pressure (hPa) %0.2f\n",Opres);
  display.printf("Humidity (%rH)  %0.2f\n",Ohum);
  display.printf("Dust Level: %0.2f \n",Odust);
  display.printf("Moisture: %d \n",Omoist);
  display.display();
}

float getDust() {
  unsigned long duration;
  unsigned long starttime;
  unsigned long sampletime_ms = 30000;//sampe 30s ;
  unsigned long lowpulseoccupancy = 0;
  float ratio = 0;
  float concentration = -1;

  pinMode(DUSTPIN,INPUT);
  starttime = millis();//get the current time;

  while(concentration == -1) {
    duration = pulseIn(DUSTPIN, LOW);
    lowpulseoccupancy = lowpulseoccupancy+duration;

    if ((millis()-starttime) > sampletime_ms)//if the sampel time == 30s
    {
        ratio = lowpulseoccupancy/(sampletime_ms*10.0);  // Integer percentage 0=>100
        concentration = 1.1*pow(ratio,3)-3.8*pow(ratio,2)+520*ratio+0.62; // using spec sheet curve
        Serial.print(lowpulseoccupancy);
        Serial.print(",");
        Serial.print(ratio);
        Serial.print(",");
        Serial.println(concentration);
        lowpulseoccupancy = 0;
        starttime = millis();
    }
  }
return concentration;
}