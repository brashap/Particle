/*
 * Project: PotHole
 * Description: Use GY-21 to detect pot holes, tag with GSP, and save to SD Card
 * Author: Brian Rashap
 * Date: 03-May-2020
 */

#include "Particle.h"
#include "credentials.h"
#include "TinyGPS++.h"
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"
#include "Time.h"
#include "SPI.h"
#include "SdFat.h"
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT/Adafruit_MQTT.h" 
#include "Adafruit_MQTT/Adafruit_MQTT_SPARK.h" 
#include "Adafruit_MQTT/Adafruit_MQTT.h" 
#include "JsonParserGeneratorRK.h"

// Configure microSD
const int chipSelect = D3;
#define FILE_BASE_NAME "Data"
SdFat SD;
SdFile file;
const uint8_t BASE_NAME_SIZE = sizeof(FILE_BASE_NAME) - 1;
char fileName[13] = FILE_BASE_NAME "00.csv";

// Configure OLED Display
#define OLED_RESET D4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(OLED_RESET);

SYSTEM_THREAD(ENABLED);

const unsigned long PUBLISH_PERIOD = 50000;
const unsigned long SERIAL_PERIOD = 2500;
const unsigned long MAX_GPS_AGE_MS = 5000;

// Configure GPS
TinyGPSPlus gps;
#define Uart Serial1
//void gpsdump(TinyGPS &gps);
const int UTC_offset = -7;   // Mountain Daylight Time
unsigned long lastSerial = 0;
unsigned long lastPublish = 0;
unsigned long startFix = 0;
bool gettingFix = false;

float lat,lon,alt;
float lat_ref, lon_ref;
void printFloat(double f, int digits = 2);

// Configure MPU6060
const int MPU_ADDR = 0x68; // I2C address of the MPU-6050. If AD0 pin is set to HIGH, the I2C address will be 0x69.

// Adafruit.io Setup
#define AIO_SERVER      "io.adafruit.com" 
#define AIO_SERVERPORT  1883                   // use 8883 for SSL 
TCPClient TheClient; 
Adafruit_MQTT_SPARK mqtt(&TheClient,AIO_SERVER,AIO_SERVERPORT,AIO_USERNAME,AIO_KEY); 
Adafruit_MQTT_Publish pothole = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/pothole/json");
unsigned long lastPing;
unsigned long lastAIOpublish;

// Declare Variables
const float threshold=1.10;
int startPin=D8;
int zPin=A5;
int ledPin=A1;
float zAcc;
float cal;
int i;
bool logStart;

SYSTEM_MODE(SEMI_AUTOMATIC);

void setup() {

  Serial.begin(9600);
  Uart.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  // Initialize MPU6050
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR); // Begins a transmission to the I2C slave (GY-521 board)
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0); // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);

  pinMode(startPin,INPUT);
  pinMode(ledPin,OUTPUT);

  display.setTextSize(1);             
  display.setTextColor(WHITE);
  display.clearDisplay();

  // Calibrate Accelerometer

  display.setCursor(0,0);
  display.clearDisplay();
  display.printf("Begin Calibration\n");
  display.display();
  delay(2000);

  for(i=0;i<20;i++) {
    cal += getBump();
    delay(250);
  }
  cal = cal / 20.0;
  display.setCursor(0,0);
  display.clearDisplay();
  display.printf("Calibration = %0.2f",cal);
  display.display();
  delay(2000);
  

  // Initialize microSD
  if (!SD.begin(chipSelect, SD_SCK_MHZ(50))) {
    SD.initErrorHalt();  
  }
  if (BASE_NAME_SIZE > 6) {
    Serial.println("FILE_BASE_NAME too long");
    while(1);
  }
  
  // Get inital GPS
  display.setCursor(0,16);             // Start at top-left corner
  display.println("GPS Acquiring"); 
  display.display();
  getGPS();

  logStart = false;
  Serial.println("Push button to begin");
 
}

void loop() {
  logStart=digitalRead(startPin);
  if (logStart==true) {
    Serial.printf("Starting Data Logging \n");
    digitalWrite(ledPin,HIGH);
    // while (SD.exists(fileName)) {
    //   if (fileName[BASE_NAME_SIZE + 1] != '9') {
    //     fileName[BASE_NAME_SIZE + 1]++;
    //   } else if (fileName[BASE_NAME_SIZE] != '9') {
    //     fileName[BASE_NAME_SIZE + 1] = '0';
    //     fileName[BASE_NAME_SIZE]++;
    //   } else {
    //     Serial.println("Can't create file name");
    //     while(1);
    //   }
    }
    // if (!file.open(fileName, O_WRONLY | O_CREAT | O_EXCL)) {
    //   Serial.println("file.open");
    //   //file.printf("TimeStamp, Acceleration,Latitude-Longitude \n");
    //   file.print("Time, Lat, Lon, Acceleration \n");
    // }
    // Serial.printf("Logging to: %s \n",fileName);
    delay(1000); //give chance to release button
  }
  while(logStart==true) {
    MQTT_connect();

    if ((millis()-lastPing)>60000) {
      Serial.printf("Pinging MQTT \n");
      if(! mqtt.ping()) {
        Serial.printf("Disconnecting \n");
        mqtt.disconnect();
      }
      lastPing = millis();
    }
    if(millis()-lastAIOpublish > 30000) {
      if(mqtt.Update()) {
      createEventPayLoad(zAcc, lat, lon, alt);
      } 
      lastAIOpublish = millis();
    }
    // if (!file.sync() || file.getWriteError()) {
    // Serial.printf("write error");
    // }
    logStart =  !digitalRead(startPin);
    if (logStart==false) {
      // file.close();
      Serial.printf("Done \n");
      digitalWrite(ledPin,LOW);
      delay(2000);
      Serial.printf("Ready for next data log \n");
    }
  }
}

void getGPS() {
  bool newdata = false;
  unsigned long start = millis();
  Serial.println("Begin Acquire");

  // Every 5 seconds we print an update
  while (millis() - start < 5000) {
    if (Uart.available()) {
      char c = Uart.read();
      Serial.print(c);  // uncomment to see raw GPS data
      if (gps.encode(c)) {
        newdata = true;
        break;  // uncomment to print new data immediately!
      }
    }
  }
  if (newdata) {
    Serial.println("Acquired Data");
    Serial.println("-------------");
    displayInfo();
    Serial.println("-------------");
    Serial.println();
  }
}

void SDlonglat() {
  float lat,lon,alt;
  uint8_t hr,mn,se,cs,sat;
  lat = gps.location.lat();
  lon = gps.location.lng();
  alt = gps.altitude.meters();
  hr = gps.time.hour();
  mn = gps.time.minute();
  se = gps.time.second();
  cs = gps.time.centisecond();
  sat = gps.satellites.value();
			
      if(hr > 7) {
				hr = hr + UTC_offset;
			}
			else {
				hr = hr + 24 + UTC_offset;
			}

  Serial.printf("Time: %02i:%02i:%02i:%02i --- ",hr,mn,se);
  Serial.printf("lat: %f, long: %f, alt: %f \n", lat,lon,alt);
  //file.printf("Time: %02i:%02i:%02i:%02i --- ",hr,mn,se);
  //file.printf("lat: %f, long: %f, alt: %f \n", lat,lon,alt);
  file.printf("%02i:%02i:%02i,%f,%f,%f\n",hr,mn,se,lat,lon,zAcc);
  //gotBump();
}

void displayInfo() {
	float lat,lon,alt;
	uint8_t hr,mn,se,cs,sat;
	if (millis() - lastSerial >= SERIAL_PERIOD) {
		lastSerial = millis();

		char buf[128];
		if (gps.location.isValid() && gps.location.age() < MAX_GPS_AGE_MS) {
			lat = gps.location.lat();
			lon = gps.location.lng(); 
			alt = gps.altitude.meters();
			hr = gps.time.hour();
			mn = gps.time.minute();
			se = gps.time.second();
			cs = gps.time.centisecond();
			sat = gps.satellites.value();

			if(hr > 7) {
				hr = hr + UTC_offset;
			}
			else {
				hr = hr + 24 + UTC_offset;
			}
			Serial.printf("Time: %02i:%02i:%02i:%02i --- ",hr,mn,se,cs);
			Serial.printf("lat: %f, long: %f, alt: %f \n", lat,lon,alt);
			if (gettingFix) {
				gettingFix = false;
				unsigned long elapsed = millis() - startFix;
				Serial.printlnf("%lu milliseconds to get GPS fix", elapsed);
			} 
      gotBump();
      delay(1000);
			display.clearDisplay();
			display.setCursor(0,0);
			display.printf("Time: %02i:%02i:%02i \n",hr,mn,se);
			display.printf("lat    %f \nlong %f \nalt %f\n", lat,lon,alt);
			display.printf("satelites %i \n", sat);
			//display.printf("Distance = %0.2f \n",gps.distanceBetween(lat,lon,lat_ref,lon_ref));
			display.display();
      // SDlonglat();
		}
		else {
			strcpy(buf, "no location");
			if (!gettingFix) {
				gettingFix = true;
				startFix = millis();
			}
		}
	}
}

float getBump() {

int16_t accel_z; // variables for accelerometer raw data
const float zscale = 18200;
float Az;

  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3F); // starting with register 0x3B (ACCEL_XOUT_H) [MPU-6000 and MPU-6050 Register Map and Descriptions Revision 4.2, p.40]
  Wire.endTransmission(false); // the parameter indicates that the Arduino will send a restart. As a result, the connection is kept active.
  Wire.requestFrom(MPU_ADDR, 2, true); // request a total of 7*2=14 registers
  
  // "Wire.read()<<8 | Wire.read();" means two registers are read and stored in the same variable
  accel_z = Wire.read()<<8 | Wire.read(); // reading registers: 0x3F (ACCEL_ZOUT_H) and 0x40 (ACCEL_ZOUT_L)
  Az = accel_z /zscale; //9.8067;

  // print out data
  //Serial.printf("accX = %i | accY = %i | accZ = %i | aX = %0.2fG  | aY = %0.2fG | aZ = %0.2fG \n",accel_x,accel_y,accel_z,Ax,Ay,Az);
  //Serial.printf("aZ = %0.2fG \n",Az);
  return Az;
}

void gotBump() {
  display.setTextSize(2);             
  display.setTextColor(WHITE);
  display.clearDisplay();
  display.setCursor(0,10);
  display.printf("  Bump  \nDetected\n");
  display.display();
  display.setTextSize(1);

}

void MQTT_connect() {
  int8_t ret;
 
  if (mqtt.connected()) {
    return;
  }
 
  Serial.print("Connecting to MQTT... ");
 
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying MQTT connection in 5 seconds...");
    mqtt.disconnect();
    delay(5000);  // wait 5 seconds
  }
  Serial.println("MQTT Connected!");
}

void  createEventPayLoad (float zAcc, float lat, float lon, float alt) {

  zAcc = getBump()/cal;
    if (zAcc > threshold) { 
      Serial.printf("Z Acceleration = %0.2f \n",zAcc); 
      getGPS();
    }

  JsonWriterStatic<256> jw;
  {
    JsonWriterAutoObject obj(&jw);

    jw.insertKeyValue("zAcc", zAcc);
    jw.insertKeyValue("lat", lat);
    jw.insertKeyValue("lon", lon);
    jw.insertKeyValue("alt", alt);
  }
  pothole.publish(jw.getBuffer());
}