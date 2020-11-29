/*
 * Project OLED2
 * Description: Display BME680 Environmental Data on OLED displau
 * Author: Brian Rashap
 * Date: 11-Feb-2020
 */

#include "Particle.h"
#include "Adafruit_Sensor.h"
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include "Adafruit_BME680.h"

#define SEALEVELPRESSURE_HPA (1013.25)

// OLED display TWI address
#define OLED_ADDR   0x3C

// Define I2C Devices
Adafruit_SSD1306 display(-1);
Adafruit_BME680 bme;

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

/*=========================================================================
    SSD1306 Displays
    -----------------------------------------------------------------------
    The driver is used in multiple displays (128x64, 128x32, etc.).
    Select the appropriate display below to create an appropriately
    sized framebuffer, etc.

    SSD1306_128_64  128x64 pixel display

    SSD1306_128_32  128x32 pixel display

    SSD1306_96_16

    -----------------------------------------------------------------------*/
   #define SSD1306_128_64
//   #define SSD1306_128_32
//   #define SSD1306_96_16

unsigned long delayTime = 5000;
double tempC;
double humid;
double press;
double gas;
int i;

void setup() {

  Serial.begin(9600);
  Wire.begin();

  unsigned status;
  status = bme.begin();
  if (!status) {
    Serial.println("Could not find a valid BME680 sensor, check wiring!");
    while (1);
  }

    // Set up oversampling and filter initialization
    bme.setTemperatureOversampling(BME680_OS_8X);
    bme.setHumidityOversampling(BME680_OS_2X);
    bme.setPressureOversampling(BME680_OS_4X);
    bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
    bme.setGasHeater(320, 150); // 320*C for 150 ms

   // initialize and clear display
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();
  display.display();

  printhello();

delay(delayTime);

}

void loop() {

  for (i=0;i<12;i++) { 
    printValues();
    oledprint();
    delay(delayTime);
  }
  printhello();
  delay(delayTime);
}


void printValues()
{
    Serial.print("Temperature = ");
    Serial.print(bme.readTemperature());
    Serial.println(" *C");
    tempC = bme.readTemperature();

    Serial.print("Pressure = ");
    Serial.print(bme.readPressure() / 100.0F);
    Serial.println(" hPa");

    Serial.print("Approx. Altitude = ");
    Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
    Serial.println(" m");

    Serial.print("Humidity = ");
    Serial.print(bme.readHumidity());
    Serial.println(" %");
    humid = bme.readHumidity();

    Serial.print("Gas = ");
    Serial.print(bme.gas_resistance / 1000.0);
    Serial.println(" KOhms");

    Serial.println(); 
}

void oledprint() {

  tempC = bme.readTemperature();
  press = bme.readPressure() / 100.0F;
  humid = bme.readHumidity();
  gas = bme.gas_resistance / 1000.0;

   // initialize and clear display
  display.clearDisplay();
  display.display();

  // display a pixel in each corner of the screen
  display.drawPixel(0, 0, WHITE);
  display.drawPixel(127, 0, WHITE);
  display.drawPixel(0, 63, WHITE);
  display.drawPixel(127, 63, WHITE);

  // display a line of text
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,5);
  display.print("Environmental Reading");
  display.setCursor(0,18);
  display.print("Temperature(C) ");
  display.setCursor(94,18);
  display.print(tempC);
  display.setCursor(0,28);
  display.print("Pressure (hPa)  ");
  display.setCursor(88,28);
  display.print(press);
  display.setCursor(0,38);
  display.print("Humidity (%rH)  ");
  display.setCursor(94,38);
  display.print(humid);
  display.setCursor(0,48);
  display.print("Gas Detection   ");
  display.setCursor(88,48);
  display.print(gas);


  // update display with all of the above graphics
  display.display();
}

void printhello() {
  display.clearDisplay();
  display.display();

  // display a pixel in each corner of the screen
  display.drawPixel(0, 0, WHITE);
  display.drawPixel(127, 0, WHITE);
  display.drawPixel(0, 63, WHITE);
  display.drawPixel(127, 63, WHITE);

  // display a line of text
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(27,30);
  display.print("Hello, world!");

  // update display with all of the above graphics
  display.display();
}