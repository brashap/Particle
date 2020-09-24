/*
 * Project fix
 * Description: fix the argon going into listening mode
 * Author: Brian Rashap
 * Date: 09-APR-2020
 */
#include "Particle.h"
#include "dct.h"

SYSTEM_MODE(SEMI_AUTOMATIC);

void setup() {
    const uint8_t val = 0x01;
    dct_write_app_data(&val, DCT_SETUP_DONE_OFFSET, 1);
    WiFi.on();
    WiFi.connect();
    Particle.connect();
}