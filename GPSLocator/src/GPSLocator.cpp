/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#line 1 "c:/Users/IoT_Instructor/Documents/Particle/GPSLocator/src/GPSLocator.ino"
/*
 * Project GPSLocator
 * Description: Find GPS Location
 * Author: Brian Rashap
 * Date: 04-Nov-2020
 */

#include <Particle.h>
#include <TinyGPS.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Configure OLED Display
void setup();
void loop();
void getGPS();
void printFloat(double number, int digits);
void OLEDlonglat(float longitude, float latitude);
#line 14 "c:/Users/IoT_Instructor/Documents/Particle/GPSLocator/src/GPSLocator.ino"
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(OLED_RESET);

// Configure GPS
TinyGPS gps;
#define Uart Serial1
void gpsdump(TinyGPS &gps);
const int UTC_offset = -6;   // Mountain Daylight Time
void printFloat(double f, int digits = 2);

// Declare Variables


void setup() {

  Serial.begin(9600);
  delay(100);
  Uart.begin(9600);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextSize(1);             
  display.setTextColor(WHITE);       
  display.clearDisplay();

  display.setCursor(0,16);             // Start at top-left corner
  display.println("GPS Acquiring"); 
  display.display();
}

void loop() {
  Serial.printf("GPS Acquiring at %i \n",millis()); 

  display.clearDisplay();
  display.setCursor(0,16);             // Start at top-left corner
  display.printf("GPS Acquiring %i \n",millis());
  display.display(); 
  getGPS();
  delay(30000);
}

void getGPS() {
  bool newdata = false;
  unsigned long start = millis();
  Serial.println("Begin Acquire");

  // Every 5 seconds we print an update
  while (millis() - start < 5000) {
    if (Uart.available()) {
      char c = Uart.read();
      Serial.print(c);  // uncomment to see raw GPS data
      if (gps.encode(c)) {
        newdata = true;
        //break;  // uncomment to print new data immediately!
      }
    }
  }
  if (newdata) {
    display.printf("New Data \n");
    display.display();
    Serial.println("Acquired Data");
    Serial.println("-------------");
    gpsdump(gps);
    Serial.println("-------------");
    Serial.println();
  } 
  else
  {
    display.printf("No New Data \n");
    display.display();
  }
  
}


void gpsdump(TinyGPS &gps)
{
  long lat, lon;
  float flat, flon;
  unsigned long tage, tdate, ttime, chars;
  int tyear;
  byte tmonth, tday, thour, tminute, tsecond, hundredths;
  unsigned short sentences, failed;

  gps.get_position(&lat, &lon, &tage);
  Serial.print("Lat/Long(10^-5 deg): "); Serial.print(lat); Serial.print(", "); Serial.print(lon); 
  Serial.print(" Fix age: "); Serial.print(tage); Serial.println("ms.");

  gps.f_get_position(&flat, &flon, &tage);
  Serial.print("Lat/Long(float): "); printFloat(flat, 7); Serial.print(", "); printFloat(flon, 7);
  Serial.print(" Fix age: "); Serial.print(tage); Serial.println("ms.");

  gps.get_datetime(&tdate, &ttime, &tage);
  Serial.print("Date(ddmmyy): "); Serial.print(tdate); Serial.print(" Time(hhmmsscc): ");
    Serial.print(ttime);
  Serial.print(" Fix age: "); Serial.print(tage); Serial.println("ms.");

  gps.crack_datetime(&tyear, &tmonth, &tday, &thour, &tminute, &tsecond, &hundredths, &tage);
  Serial.print("Date: "); Serial.print(static_cast<int>(tmonth)); Serial.print("/"); 
    Serial.print(static_cast<int>(tday)); Serial.print("/"); Serial.print(tyear);
  Serial.print("  Time: "); Serial.print(static_cast<int>(thour)); Serial.print(":"); 
    Serial.print(static_cast<int>(tminute)); Serial.print(":"); Serial.print(static_cast<int>(tsecond));
    Serial.print("."); Serial.print(static_cast<int>(hundredths));
  Serial.print("  Fix age: ");  Serial.print(tage); Serial.println("ms.");

/*
        // Set Time from GPS data string
        setTime(thour, tminute, tsecond, tday, tmonth, tyear);
        // Calc current Time Zone time by offset value
        adjustTime(UTC_offset * SECS_PER_HOUR); 
        time_t t=now();
        Serial.print("Time: "); 
        Serial.print(hour(t));
        Serial.print(":");
        Serial.print(minute(t));
        Serial.print(":");
        if (second(t)<10) {
          Serial.print("0");
        }
        Serial.println(second(t));
*/ 

  OLEDlonglat(flat,flon);

  Serial.print("Alt(cm): "); Serial.print(gps.altitude()); Serial.print(" Course(10^-2 deg): ");
    Serial.print(gps.course()); Serial.print(" Speed(10^-2 knots): "); Serial.println(gps.speed());
  Serial.print("Alt(float): "); printFloat(gps.f_altitude()); Serial.print(" Course(float): ");
    printFloat(gps.f_course()); Serial.println();
  Serial.print("Speed(knots): "); printFloat(gps.f_speed_knots()); Serial.print(" (mph): ");
    printFloat(gps.f_speed_mph());
  Serial.print(" (mps): "); printFloat(gps.f_speed_mps()); Serial.print(" (kmph): ");
    printFloat(gps.f_speed_kmph()); Serial.println();

  Serial.print("Satellites in view: ");
  Serial.println(gps.satellites(), DEC);

  gps.stats(&chars, &sentences, &failed);
  Serial.print("Stats: characters: "); Serial.print(chars); Serial.print(" sentences: ");
    Serial.print(sentences); Serial.print(" failed checksum: "); Serial.println(failed);
}

void printFloat(double number, int digits)
{
  // Handle negative numbers
  if (number < 0.0) {
     Serial.print('-');
     number = -number;
  }

  // Round correctly so that print(1.999, 2) prints as "2.00"
  double rounding = 0.5;
  for (uint8_t i=0; i<digits; ++i)
    rounding /= 10.0;
  
  number += rounding;

  // Extract the integer part of the number and print it
  unsigned long int_part = (unsigned long)number;
  double remainder = number - (double)int_part;
  Serial.print(int_part);

  // Print the decimal point, but only if there are digits beyond
  if (digits > 0)
    Serial.print("."); 

  // Extract digits from the remainder one at a time
  while (digits-- > 0) {
    remainder *= 10.0;
    int toPrint = int(remainder);
    Serial.print(toPrint);
    remainder -= toPrint;
  }
}

void OLEDlonglat(float longitude, float latitude) {
  display.clearDisplay();
  
  display.setCursor(0,0);             // Start at top-left corner
  /*
        time_t t=now();               // display time
        display.print("Time: "); 
        display.print(hour(t));
        display.print(":");
        display.print(minute(t));
        display.print(":");
        if (second(t)<10) {
          display.print("0");
        }
        display.println(second(t));
  */
  display.print("Longitude:  "); display.println(longitude);
  display.print("Latitude: "); display.println(latitude);  
  display.print("Satellites: "); display.println(gps.satellites(), DEC);
  display.display();
}
