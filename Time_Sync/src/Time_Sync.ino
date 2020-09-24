/*
 * Project Time_Sync
 * Description: Syncronize Time to Particle Cloud
 * Author: Brian Rashap
 * Date:   13-Jan-2020
 */

#include <Particle.h>
#define ONE_DAY_MILLIS (30*1000)   // for testing purposes, update every 30 seconds
// #define ONE_DAY_MILLIS (24 * 60 * 60 * 1000)  // normal operation, sync every day

void setup() {
  Serial.begin();
  while(!Serial); // wait for Serial monitor
  Serial.println("----------- Begin Time Sync ------------");
}

void loop() {
  time_t lastSyncTimestamp; // time_t is the UNIX time at last sync
  Time.zone(-7); // Set Time Zone to Mountain (UTC - 7)
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
}