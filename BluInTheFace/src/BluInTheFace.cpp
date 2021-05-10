/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "c:/Users/IoTPa/Documents/Particle/BluInTheFace/src/BluInTheFace.ino"
/*
 * Project BluInTheFace
 * Description: Simple BLE Scanner - prints MAC address and signal strength
 * Author: Brian Rashap
 * Date: 26-AUG-2020
 */

void setup();
void loop();
void bleFound(const BleScanResult *scanResult, void *context);
#line 8 "c:/Users/IoTPa/Documents/Particle/BluInTheFace/src/BluInTheFace.ino"
const unsigned long reScan = 60000;
unsigned long lastScan;
byte mac[6];

void setup() {
  Serial.begin(9600);
  delay(1000);
  BLE.setScanTimeout(500);
  lastScan = 0;
  WiFi.macAddress(mac);
  Serial.printf("WiFi MAC: %02X:%02X:%02X:%02X:%02X:%02X \n ", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  Serial.printf("Argon BLE Address: %s",BLE.address().toString().c_str());
}

void loop() {
  if((millis()-lastScan) > reScan){
    Serial.printf("\n \n \n--------------------\n");
    Serial.printf("Scanning for Devices\n");
    Serial.printf("--------------------\n");
    BLE.scan(bleFound, NULL);
    lastScan = millis();
  } 
}

void bleFound(const BleScanResult *scanResult, void *context) {
  int uuidsAvail;
  BleUuid uuids[4];
  
  uuidsAvail = scanResult->advertisingData.serviceUUID(uuids,sizeof(uuids)/sizeof(BleUuid));

  // Print out mac info
  BleAddress addr = scanResult->address;
  Serial.printf("MAC: %02X:%02X:%02X:%02X:%02X:%02X --- ", addr[0], addr[1], addr[2], addr[3], addr[4], addr[5]);
  Serial.printf("RSSI: %i dBm \n", scanResult->rssi);  
}