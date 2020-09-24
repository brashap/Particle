/*
 * Project RelayTest
 * Description: It would be nice if something worked this morning
 * Author: Brian Rashap
 * Date: 24-APR-2020
 */

int pinRelay = D11;
int pinButton = D8;
int pinLED = D7;

void setup() {
pinMode(pinRelay,OUTPUT);
pinMode(pinButton,INPUT);
pinMode(pinLED,OUTPUT);
}

void loop() {
digitalWrite(pinLED,digitalRead(pinButton));
digitalWrite(pinRelay,digitalRead(pinButton));
}
