/*
 * Project CharAsciiTest
 * Description:
 * Author:
 * Date:
 */

const int degree = 0xB0;
float temp = 98.6;

void setup() {
  Serial.begin(9600);
  delay(1000);
  Serial.printf("My temperature is %0.1f %c",temp,degree);
}