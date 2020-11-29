/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "c:/Users/IoT_Instructor/Documents/Particle/PointerFun2/src/PointerFun2.ino"
/*
 * Project PointerFun2
 * Description:
 * Author:
 * Date:
 */

void setup();
void loop();
#line 8 "c:/Users/IoT_Instructor/Documents/Particle/PointerFun2/src/PointerFun2.ino"
int data = 13;
int data2;
int *ptr;

void setup() {
  Serial.begin(9600);
  delay(1000);
  ptr = &data;          //point ptr to the memory location of data
  data2 = *ptr;         //set data2 to value of data (13)

  // Print the Value and Address of the Variables
  Serial.printf("Variable         Value      Address \n");
  Serial.printf("  data            %i       0x%X   \n",data, &data);
  Serial.printf("  ptr         0x%X   0x%X   \n",ptr, &ptr);
  Serial.printf("  data2           %i       0x%X   \n",data2, &data2);
}

void loop() {}