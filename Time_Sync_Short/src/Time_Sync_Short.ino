/*
 * Project Time_Sync_Short
 * Description: Function to Sync Time to Particle Cloud
 * Author: Brian Rashap 
 * Date:   13-Jan-2020
 */

#include <Particle.h>

void setup() {
  Serial.begin();
  while(!Serial); // wait for Serial monitor
  Serial.println("-------- Begin Time Sync --------");
}

void loop() {
  sync_my_time();
  delay(random(10000,60000));
}

void sync_my_time() {
  Time.zone(-7); // Set Time Zone to Mountain (UTC - 7)
  unsigned long cur = millis();
  
    // Request time synch from Particle Device Cloud
    Particle.syncTime();
   
    // Wait to receives time from Particle Device Cloud 
    waitUntil(Particle.syncTimeDone);
    // Check if synchronized successfully
    if (Particle.timeSyncedLast() >= cur)
    {
      // Print current time
      Serial.print("The current time (MST) is: ");
      Serial.println(Time.timeStr());
      Serial.printlnf("Current time is %s",Time.timeStr().c_str());
    }
}