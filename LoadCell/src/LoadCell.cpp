/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "c:/Users/IoT_Instructor/Documents/Particle/LoadCell/src/LoadCell.ino"
/*
 * Project LoadCell
 * Description:
 * Author:
 * Date:
 */


#include "HX711.h"    

void setup();
void loop();
#line 11 "c:/Users/IoT_Instructor/Documents/Particle/LoadCell/src/LoadCell.ino"
#define DOUT  12
#define CLK 11

HX711 scale(DOUT, CLK);

float calibration_factor = 242; //-7050 worked for my 440lb max scale setup

float value;
float  sc;
long   off;
double  raw;

void setup() {
  Serial.begin(9600);
  Serial.println("HX711 calibration sketch");
  Serial.println("Remove all weight from scale");

  scale.set_scale();
  Serial.println("Setting Zero");
  delay(5000);
  scale.tare();  //Reset the scale to 0

  long zero_factor = scale.read_average(); //Get a baseline reading
  Serial.print("Zero factor: "); //This can be used to remove the need to tare the scale. Useful in permanent scale projects.
  Serial.println(zero_factor);
  scale.set_scale(calibration_factor); //Adjust to this calibration factor
}

void loop() {

  value = scale.get_units(1);
  sc = scale.get_scale();
  off = scale.get_offset();
  raw = scale.get_value(1);

  Serial.printf("Reading: %0.2f. Scale = %0.2f, Offset = %i, Raw = %0.2f \n", value, sc, off, raw);

  delay(5000);
}