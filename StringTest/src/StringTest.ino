/*
 * Project StringTest
 * Description:
 * Author:
 * Date:
 */

String name;


// setup() runs once, when the device is first turned on.
void setup() {
  Serial.begin(9600);
  delay(1000);
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  name = "Kaleb";

  Serial.printf("My name is %s \n",name.c_str());

  name = "Thomas";
  Serial.printf("My new name is %s \n",name.c_str());

}