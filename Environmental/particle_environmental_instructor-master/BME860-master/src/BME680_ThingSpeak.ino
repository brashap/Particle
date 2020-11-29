/*
 * Project BME680_ThingSpeak
 * Description: BME680 Temp, Pressure, Humidity, and Air Quality
 *              Send multiple values to Thingspace
 * Author: Brian Rashap
 * Date: 10/23/2019
 */

#include "Particle.h"
#include "Adafruit_Sensor.h"
// #include "Adafruit_BME280.h"
#include "Adafruit_BME680.h"
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>



#define SEALEVELPRESSURE_HPA (1013.25)

// Adafruit_BME280 bme; // I2C
Adafruit_BME680 bme; // I2C
// SeeedOLED oled;       //I2C

unsigned long delayTime;
unsigned int i;
double tempC;
double humid;
double press;
double gas;


//  [ Specific Values for each Installation of a ThingSpeak Channel ]
////////////////////////////////////////////////////
const char * eventName =            "FUSEMakerspace";       //  This must match the name of the event you chose for the WebHook
unsigned long publish_delay =       30000;                  //  (ms)  Multiply # of Seconds * 1000. This is how often ThingSpeak will be updated.  30,000 = 30 Seconds
//ThingSpeak Channel Info                                   //
const char * myWriteAPIKey = "7XT8QXBIBTJ3E020";            //  From your ThinkSpeak Account Info (API KEYS tab), WRITE API Key
////////////////////////////////////////////////////

unsigned long previousPublish =      0   ;    // store last Publish Time
char msg[256];       // Character array for the snprintf Publish Payload

// OLED display TWI address
#define OLED_ADDR   0x3C

// Define I2C Devices
Adafruit_SSD1306 display(-1);

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



void setup() {
    Wire.begin();

    Particle.variable("temp", tempC); 

    Serial.begin(9600);
    delay(500);  // time to get serial running
    Serial.println("BME680 test");
    // oled.init();                      // Initialze SSD1306 OLED display
    unsigned status;

    // default settings
    // (you can also pass in a Wire library object like &Wire2)
    status = bme.begin();
    if (!status) {
      Serial.println("Could not find a valid BME680 sensor, check wiring!");
      while (1);
    }
  
  // initialize and clear display
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();
  display.display();
  printhello();

    // Set up oversampling and filter initialization
    bme.setTemperatureOversampling(BME680_OS_8X);
    bme.setHumidityOversampling(BME680_OS_2X);
    bme.setPressureOversampling(BME680_OS_4X);
    bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
    bme.setGasHeater(320, 150); // 320*C for 150 ms

    delayTime = 30000;
}

void loop()
{
  for (i=0;i<12;i++) { 
    printValues();
    oledprint();

    String temp = String(tempC);
    String hum = String(humid);

    // Perform whatever Actions you need HERE to update the float values for field1, field2, etc

    // Prepare the Publish Payload using snprintf to avoid Strings:
    snprintf(msg, sizeof(msg),
    // ThingSpeak Field #1  , ThingSpeak Field #2   ,  ThingSpeak WriteKey
       "{\"1\":\"%.2f\"     ,   \"2\":\"%.2f\"      ,   \"k\":\"%s\"}"      ,
    // Float for Field #1   , Float for Field #2    ,  ThingSpeak WriteKey
            tempC          ,       humid          ,   myWriteAPIKey)      ;

    // after you understand the snprintf format, remove the extra spaces in your final code, to look like this instead:
    // snprintf(msg, sizeof(msg), "{\"1\":\"%.1f\",\"2\":\"%.1f\",\"k\":\"%s\"}", field1, field2, myWriteAPIKey);

    // Note:    %.1f = 1 decimal place for a FLOAT number, many other options available.
    //          %.2f = 2 decimal places for a FLOAT
    //          %s   = String, normally just used for the ThingSpeak API Key
    // You can update all 8 Fields of a ThingSpeak Channel during 1 Publish, just add to the snprintf.

    Particle.publish(eventName, msg, PRIVATE, NO_ACK);  // perform the Publish
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
/*
void OLED_print() {
  oled.clearDisplay();              // Clear screen
  oled.setTextXY(0,0);              // Set cursor position, start of line 0
  oled.putString("IoT Classroom");
  oled.setTextXY(1,0);              // Set cursor position, start of line 1
  oled.putString("BME 680");
  oled.setTextXY(2,0);              // Set cursor position, start of line 2
  oled.putString("Temp (C) = ");
  oled.setTextXY(2,12);             // Set cursor position, line 2 10th character
  oled.putString(String(tempC)); 
}
*/


/*
  Create a Particle Webhook manually at  https://console.particle.io/integrations/webhooks/create
    Click [CUSTOM TEMPLATE]
    Copy/Paste the following into the CODE window:

  {
  "event": "TEST",
  "url": "https://api.thingspeak.com/update",
  "requestType": "POST",
  "form": {
  "api_key": "{{k}}",
  "field1": "{{1}}",
  "field2": "{{2}}",
  "field3": "{{3}}", 
  "field4": "{{4}}",
  "field5": "{{5}}",
  "field6": "{{6}}",
  "field7": "{{7}}",
  "field8": "{{8}}",
  "lat": "{{a}}",
  "long": "{{o}}",
  "elevation": "{{e}}",
  "status": "{{s}}"
  },
  "mydevices": true,
  "noDefaults": true
  }

  CLICK: "CREATE WEBHOOK"
  
    You will change the "event" in the first line of the JSON to whatever event name you wish:
    The Example names the WebHook's event: "TEST",
    So you make sure the CODE (for Photon or Electron) below under [Specific Values for each Installation] is :
    const char * eventName = { Must match the WebHook event name }
    Note: 1 webhook will work for multiple devices.  Use a different eventName if you want to track how many publishes any particular device makes daily/monthly. 

*/

/*
//  [ Specific Values for each Installation ]
////////////////////////////////////////////////////
const char * eventName =            "FUSEMakerspace";       //  This must match the name of the event you chose for the WebHook
unsigned long publish_delay =       30000;                  //  (ms)  Multiply # of Seconds * 1000. This is how often ThingSpeak will be updated.  30,000 = 30 Seconds
//ThingSpeak Channel Info                                   //
const char * myWriteAPIKey = "7XT8QXBIBTJ3E020";            //  From your ThinkSpeak Account Info (API KEYS tab), WRITE API Key
////////////////////////////////////////////////////

unsigned long previousPublish =      0   ;    // store last Publish Time
char msg[256];       // Character array for the snprintf Publish Payload


void setup() {
} // end Setup


void loop() {

  if (millis()  - previousPublish >= publish_delay) {  // it's time to publish

    // Perform whatever Actions you need HERE to update the float values for field1, field2, etc

    // Prepare the Publish Payload using snprintf to avoid Strings:
    snprintf(msg, sizeof(msg),
    // ThingSpeak Field #1  , ThingSpeak Field #2   ,  ThingSpeak WriteKey
       "{\"1\":\"%.1f\"     ,   \"2\":\"%.1f\"      ,   \"k\":\"%s\"}"      ,
    // Float for Field #1   , Float for Field #2    ,  ThingSpeak WriteKey
            field1          ,       field2          ,   myWriteAPIKey)      ;

    // after you understand the snprintf format, remove the extra spaces in your final code, to look like this instead:
    // snprintf(msg, sizeof(msg), "{\"1\":\"%.1f\",\"2\":\"%.1f\",\"k\":\"%s\"}", field1, field2, myWriteAPIKey);

    // Note:    %.1f = 1 decimal place for a FLOAT number, many other options available.
    //          %.2f = 2 decimal places for a FLOAT
    //          %s   = String, normally just used for the ThingSpeak API Key
    // You can update all 8 Fields of a ThingSpeak Channel during 1 Publish, just add to the snprintf.

    Particle.publish(eventName, msg, PRIVATE, NO_ACK);  // perform the Publish
    previousPublish = millis();                         // update the time of the last Publish.
    
    field1 = field1 + 1;  // change the values for demo
    field2 = field2 + 1; 
    
  }

} // End Loop
*/