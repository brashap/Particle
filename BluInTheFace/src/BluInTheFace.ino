/*
 * Project BluInTheFace
 * Description: Simple BLE Scanner - prints MAC address and signal strength
 * Author: Brian Rashap
 * Date: 26-AUG-2020
 */

const unsigned long reScan = 60000;
unsigned long lastScan;
byte mac[6];

void setup() {
  Serial.begin(9600);
  BLE.setScanTimeout(500);
  lastScan = 0;
  WiFi.macAddress(mac);
  Serial.printf("WiFi MAC: %02X:%02X:%02X:%02X:%02X:%02X \n ", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  //BLE.macAddress(mac);
  //Serial.printf("BLE MAC: %02X:%02X:%02X:%02X:%02X:%02X --- ", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
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