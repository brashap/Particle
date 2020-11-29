/*
 * Project PointerFun
 * Description: Using Pointers
 * Author: Brian Rashap
 * Date: 27-AUG-2020
 */

int xArray[4];
int yArray[256];

int *pointerX;
int *pointerY;
int i;
float average;
int sizeX, sizeY;

void setup() {
  Serial.begin(9600);
  delay(200);

  pointerX=&xArray[0];
  sizeX=sizeof(xArray)/4;
  pointerY=&yArray[0];
  sizeY=sizeof(yArray)/4;

  for(i=0;i<sizeX;i++) {
    xArray[i] = random(0,255);
  }

  for(i=0;i<sizeY;i++) {
    yArray[i] = random(256,512);
  }

  average = getAve(pointerX, sizeX);
  Serial.printf("Array X Average = %0.2f \n", average);

  average = getAve(pointerY, sizeY);
  Serial.printf("Array Y Average = %0.2f \n", average);

  //Print Pointers Addresses
  Serial.printf("xArray[0] value: %3i, *pointerX:     %3i, pointerX:   0x%X \n",xArray[0],*pointerX,pointerX);
  Serial.printf("xArray[1] value: %3i, *(pointerX+1): %3i, pointerX+1: 0x%X \n",xArray[1],*(pointerX+1),(pointerX+1));
  Serial.printf("xArray[2] value: %3i, *(pointerX+2): %3i, pointerX+2: 0x%X \n",xArray[2],*(pointerX+2),(pointerX+2));
  Serial.printf("xArray[3] value: %3i, *(pointerX+3): %3i, pointerX+3: 0x%X \n",xArray[3],*(pointerX+3),(pointerX+3));
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {}

float getAve(int *array,int size) {
  int j;
  float total=0;
  int max=0;

  for(j=0;j<size;j++) {
    total += array[j];
  }
  return total/size;
}