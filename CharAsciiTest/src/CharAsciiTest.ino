/*
 * Project CharAsciiTest
 * Description:
 * Author:
 * Date:
 */

#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"

#define OLED_RESET D4
Adafruit_SSD1306 display(OLED_RESET);

const char degree = 0xA7;
float temp = 98.6;

void setup() {
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); 
  display.display();
  delay(1000);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
}

void loop() {
  Serial.printf("My temperature is %0.1f%c\n",temp,degree);
  display.printf("THIS IS A TEST \n");
  display.printf("My temp is %0.1f%cF\n",temp,degree);
  display.display();
  delay(2000);
}