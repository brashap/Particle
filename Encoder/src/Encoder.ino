/*
 * Project Encoder
 * Description:
 * Author:
 * Date:
 */

#include <math.h>

Servo myServo;
float i;
int angle;
long thetime;

#include <SparkFun_Qwiic_Twist_Arduino_Library.h>
TWIST twist; //Create instance of this object

void setup() {
  Serial.begin(9600);
  Serial.println("Qwiic Twist Example");

  myServo.attach(A1);

  if(twist.begin() == false)
  {
    Serial.println("Twist does not appear to be connected. Please check wiring. Freezing...");
    while(true);
  }
  twist.setColor(random(0,64), random(0,64), random(0,64));  // set encoder color to Pink
  myServo.write(0);
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {

  //Has the user twisted the knob recently?
  if (twist.isMoved())
  {
    Serial.printf("Count %i ",twist.getCount());
    //Print how long it's been since user twisted the knob
    thetime = twist.timeSinceLastMovement();
    Serial.printf("Last Twist Time: %i \n",thetime);
  }

  /*if (twist.isClicked());
  {
    Serial.printf(" Last Button Time: %i \n",twist.timeSinceLastPress());
  }*/

  //if (twist.isPressed()) Serial.print(" Pressed! /n"); 
}