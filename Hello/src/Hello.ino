/*
 * Project hello
 * Description:
 * Author:
 * Date:
 */

void setup() {
  Serial.begin();
  pinMode(D7,OUTPUT);
}

void loop() {
  Serial.printf("Random Number: %i \n ",random(0,43));
  digitalWrite(D7,HIGH);
  delay(1000);
  digitalWrite(D7,LOW);
  delay(1000);
}