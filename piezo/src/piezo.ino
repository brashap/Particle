/*
 * Project piezo
 * Description:
 * Author:
 * Date:
 */

// setup() runs once, when the device is first turned on.
void setup() {
  Serial.begin(9600);
  delay(2000);
  pinMode(A3,INPUT);
  Serial.print("Begin");
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  Serial.printf("Reading = %i \n",analogRead(A3));
  delayMicroseconds(500);
}