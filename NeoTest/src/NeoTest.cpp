/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "c:/Users/IoT_Instructor/Documents/Particle/NeoTest/src/NeoTest.ino"
#include "neopixel.h"

// IMPORTANT: Set pixel COUNT, PIN and TYPE
#line 4 "c:/Users/IoT_Instructor/Documents/Particle/NeoTest/src/NeoTest.ino"
void setup();
void loop();

#define PIXEL_PIN D2
#define PIXEL_COUNT 10
#define PIXEL_TYPE WS2812B

int i;
int red = 0xFF0000;

Adafruit_NeoPixel pixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);


SYSTEM_MODE(SEMI_AUTOMATIC);

void setup() {
  pixel.begin();
  pixel.show();
}


void loop() {
  for(i=0;i<4;i++) {
    pixel.setPixelColor(i,red);
  }
  pixel.show();
}