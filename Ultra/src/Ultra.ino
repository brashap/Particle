/*
 * Project Ultra
 * Description:
 * Author:
 * Date:
 */

float cm = 0.0;
int trigPin = D4;
int echoPin = D5;

void setup() 
{
  Serial.begin(9600);
  delay(500);
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
}

void loop() 
{
    
  sendTriggerPulse(trigPin);
  waitForEcho(echoPin, HIGH, 100);
  long startTime = micros();
  waitForEcho(echoPin, LOW, 100);
  long endTime = micros();
  float duration = endTime - startTime;
  cm = duration / 58.0;
    Serial.printf("Duration = %0.2f, Distance in CM: %0.2f \n",duration,cm);
    delay(3000);
}

void waitForEcho(int pin, int value, long timeout){
    long giveupTime = millis() + timeout;
    while (digitalRead(pin) != value && millis() < giveupTime) {}
}

void sendTriggerPulse(int pin){
    digitalWrite(pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(pin, LOW);
}