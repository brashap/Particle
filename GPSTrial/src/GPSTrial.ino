/*
 * Project GPSTrial
 * Description:
 * Author:
 * Date:
 */

#include "Particle.h"

#include "AssetTrackerRK.h" // only used for AssetTracker::antennaExternal

// Port of TinyGPS for the Particle AssetTracker
// https://github.com/mikalhart/TinyGPSPlus
#include "TinyGPS++.h"

#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"

#define OLED_RESET D4
Adafruit_SSD1306 display(OLED_RESET);

SYSTEM_THREAD(ENABLED);

/*
   This sample sketch demonstrates the normal use of a TinyGPS++ (TinyGPSPlus) object directly.
 */

void displayInfo(); // forward declaration

const unsigned long PUBLISH_PERIOD = 120000;
const unsigned long SERIAL_PERIOD = 5000;
const unsigned long MAX_GPS_AGE_MS = 10000; // GPS location must be newer than this to be considered valid

// The TinyGPS++ object
TinyGPSPlus gps;
unsigned long lastSerial = 0;
unsigned long lastPublish = 0;
unsigned long startFix = 0;
bool gettingFix = false;

void setup()
{
	Serial.begin(9600);

	// The GPS module on the AssetTracker is connected to Serial1 and D6
	Serial1.begin(9600);
	display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

	// Settings D6 LOW powers up the GPS module
    pinMode(D6, OUTPUT);
    digitalWrite(D6, LOW);
    startFix = millis();
    gettingFix = true;

    // If using an external antenna, uncomment this block
    // { AssetTracker t; t.antennaExternal(); }
	helloWorld();
}

void loop()
{
	while (Serial1.available() > 0) {
		if (gps.encode(Serial1.read())) {
			displayInfo();
		}
	}

}

void displayInfo()
{
	if (millis() - lastSerial >= SERIAL_PERIOD) {
		lastSerial = millis();

		char buf[128];
		if (gps.location.isValid() && gps.location.age() < MAX_GPS_AGE_MS) {
			snprintf(buf, sizeof(buf), "%f,%f,%f", gps.location.lat(), gps.location.lng(), gps.altitude.meters());
			if (gettingFix) {
				gettingFix = false;
				unsigned long elapsed = millis() - startFix;
				Serial.printlnf("%lu milliseconds to get GPS fix", elapsed);
			}
			display.clearDisplay();
			display.printf("%f \n %f \n %f", gps.location.lat(), gps.location.lng(), gps.altitude.meters());
			display.display();
		}
		else {
			strcpy(buf, "no location");
			if (!gettingFix) {
				gettingFix = true;
				startFix = millis();
			}
		}
		Serial.println(buf);

		if (Particle.connected()) {
			if (millis() - lastPublish >= PUBLISH_PERIOD) {
				lastPublish = millis();
				Particle.publish("gps", buf, PRIVATE);
			}
		}
	}

}

void helloWorld() {
	display.clearDisplay();
	display.setTextSize(1);
  	display.setTextColor(WHITE);
  	display.setCursor(0,0);
  	display.println("Hello, world!");
	display.display();
}