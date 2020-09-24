/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/home/brian/Particle/Hello/src/Hello.ino"
// This #include statement was automatically added by the Particle IDE.
#include "neopixel.h"
#include "clickButton.h"


/*
 * Project Hello
 * Description: Hello World Test
 * Author: Brian Rashap
 * Date: 14-Oct-19
 */

void setup();
void loop();
#line 13 "/home/brian/Particle/Hello/src/Hello.ino"
int led1 = D7;
int led_delay = 5000;

// the Button
const int buttonPin1 = 4;
ClickButton button1(buttonPin1, LOW, CLICKBTN_PULLUP);

// setup() runs once, when the device is first turned on.
void setup() {
  // Put initialization like pinMode and begin functions here.
  pinMode(led1, OUTPUT);
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  // The core of your code will likely live here.
  // To blink the LED, first we'll turn it on...
  digitalWrite(led1, HIGH);

  // We'll leave it on for 1 second...
  delay(led_delay);

  // Then we'll turn it off...
  digitalWrite(led1, LOW);

  // Wait 1 second...
  delay(led_delay);

  // And repeat!
}