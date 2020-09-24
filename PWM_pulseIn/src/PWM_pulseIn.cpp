/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/home/brian/Particle/PWM_pulseIn/src/PWM_pulseIn.ino"
void setup();
void loop();
#line 1 "/home/brian/Particle/PWM_pulseIn/src/PWM_pulseIn.ino"
unsigned long duration;

void setup()
{
    Serial.begin(9600);
    while(!Serial);
    pinMode(D7, INPUT);

    // Pulse generator, connect D7 to D8
    // PWM output is 500Hz at 50% duty cycle
    // 1000us HIGH, 1000us LOW
    pinMode(D8, OUTPUT);
    analogWrite(D8, 64);
    Serial.println("Begin");
}

void loop()
{
    duration = pulseIn(D7, HIGH);
    Serial.printlnf("%d us", duration);
    delay(1000);
}