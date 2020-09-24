/*
 * Project NycoleMotion
 * Description:
 * Author:
 * Date:
 */

void setup() {
  Serial.begin(9600);
  while(!Serial);
  pinMode(A4,INPUT);

}

void loop() {
  Serial.printf("%i, %i \n",millis(), digitalRead(A4));
  delay(500);

}