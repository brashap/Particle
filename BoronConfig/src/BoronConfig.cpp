/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#line 1 "c:/Users/IoTPa/Documents/Particle/BoronConfig/src/BoronConfig.ino"
/*
 * Project BoronConfig
 * Description:
 * Author:
 * Date:
 */

#include "Particle.h"

#include "dct.h"

void setup();
void loop();
#line 12 "c:/Users/IoTPa/Documents/Particle/BoronConfig/src/BoronConfig.ino"
SYSTEM_MODE(SEMI_AUTOMATIC);

void setup() {
    Cellular.setActiveSim(EXTERNAL_SIM);
	Cellular.setCredentials("fast.t-mobile.com"); // Replace with the correct APN

	// This clears the setup done flag on brand new devices so it won't stay in listening mode
	const uint8_t val = 0x01;
    dct_write_app_data(&val, DCT_SETUP_DONE_OFFSET, 1);

	// This is just so you know the operation is complete
	pinMode(D7, OUTPUT);
	digitalWrite(D7, HIGH);
}

void loop() {
}