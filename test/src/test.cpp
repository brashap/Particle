/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "c:/Users/IoTPa/Documents/Particle/test/src/test.ino"
/*
 * Project test
 * Description:
 * Author:
 * Date:
 */

void setup();
void loop();
bool areEqual(int x[],int y[],int size);
#line 8 "c:/Users/IoTPa/Documents/Particle/test/src/test.ino"
int a[] = {1,2,3};
int b[] = {1,4,3};
int c[] = {1,2,3};
int arrSize;

void setup() {
  Serial.begin(9600);
  delay(5000);
  arrSize = sizeof(a)/4;

  if(areEqual(a,b,arrSize)){
    Serial.printf("A = B \n");
  }
  else
  {
    Serial.printf("A is not equal to B \n");
  }
  
  if(areEqual(a,c,arrSize)){
    Serial.printf("A = C \n");
  }
    else
  {
    Serial.printf("A is not equal to C \n");
  }

}

void loop() {}



bool areEqual(int x[],int y[],int size) {
  int i;

  for(i=0;i<size;i++) {
    Serial.printf("x[%i] = %i, y[%i] = %i \n",i,x[i],i,y[i]);
    if(x[i] != y[i]) {
      Serial.printf("FALSE \n");
      return false;
    }
    else
    {
      Serial.printf("TRUE \n");
    }
    
  }
  return true;
}