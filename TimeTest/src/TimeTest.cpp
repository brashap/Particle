/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#line 1 "/home/brian/Particle/TimeTest/src/TimeTest.ino"
/*
 * Project TimeTest
 * Description: Test to get time from Cloud
 * Author: Brian Rashap
 * Date: 10/23/2019
 */

#include "Particle.h"
void setup();
void loop();
#line 9 "/home/brian/Particle/TimeTest/src/TimeTest.ino"
#define ONE_DAY_MILLIS (24 * 60 * 60 * 1000)

void setup() {
    Serial.begin(9600);
    while(!Serial);// time to get serial running
    Serial.println("TIME TEST");
}

void loop() {
  time_t lastSyncTimestamp;
  Serial.println(lastSyncTimestamp);
  unsigned long lastSync = Particle.timeSyncedLast(lastSyncTimestamp);
  if (millis() - lastSync > ONE_DAY_MILLIS) {
    unsigned long cur = millis();
    Serial.printlnf("Time was last synchronized %lu milliseconds ago", millis() - lastSync);
    if (lastSyncTimestamp > 0)
    {
      Serial.print("Time received from Particle Device Cloud was: ");
      Serial.println(Time.timeStr(lastSyncTimestamp));
    }
    // Request time synchronization from Particle Device Cloud
    Particle.syncTime();
    // Wait until Argon receives time from Particle Device Cloud (or connection to Particle Device Cloud is lost)
    waitUntil(Particle.syncTimeDone);
    // Check if synchronized successfully
    if (Particle.timeSyncedLast() >= cur)
    {
      // Print current time
      Serial.println(Time.timeStr());
    }
  }
}