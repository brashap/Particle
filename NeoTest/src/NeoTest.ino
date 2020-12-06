/*
 * Project NeoTest
 * Description:
 * Author:
 * Date:
 */

#include "neopixel.h"

// IMPORTANT: Set pixel COUNT, PIN and TYPE
#define PIXEL_PIN D2
#define PIXEL_COUNT 10
#define PIXEL_TYPE WS2812B

int i;
int red = 0xFF0000;

Adafruit_NeoPixel pixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);


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