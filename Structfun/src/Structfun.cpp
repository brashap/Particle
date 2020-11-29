/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "c:/Users/IoT_Instructor/Documents/Particle/Structfun/src/Structfun.ino"
/*
 * Project Structfun
 * Description:
 * Author:
 * Date:
 */

void setup();
void loop();
#line 8 "c:/Users/IoT_Instructor/Documents/Particle/Structfun/src/Structfun.ino"
struct geo {
	float lat;
	float lon;
	int alt;
	};

geo myLoc;
geo *ptrLoc;

void setup() {
  Serial.begin(9600);
  delay(500);

  ptrLoc = &myLoc;
  myLoc.lat = 35.120606;
  myLoc.lon = -106.65818;
  myLoc.alt = 1517;
  Serial.printf("My location: lat %f, lon %f, alt %i \n",myLoc.lat,myLoc.lon,myLoc.alt);
  Serial.printf("My location: lat %f, lon %f, alt %i \n",ptrLoc->lat,ptrLoc->lon,ptrLoc->alt);
}


void loop() {}