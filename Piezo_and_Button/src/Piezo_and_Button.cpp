/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "c:/Users/IoT_Instructor/Documents/Particle/Piezo_and_Button/src/Piezo_and_Button.ino"
/*
 * Project Piezo_and_Button
 * Description:
 * Author:
 * Date:
 */

#include <SPI.h>
#include <SdFat.h>

void setup();
void loop();
void SDwrite();
void PiezoLogData();
float findAve();
#line 11 "c:/Users/IoT_Instructor/Documents/Particle/Piezo_and_Button/src/Piezo_and_Button.ino"
#define FILE_BASE_NAME "Data"

SdFat sd;
SdFile file;
const int chipSelect = SS;
  
const uint8_t BASE_NAME_SIZE = sizeof(FILE_BASE_NAME) - 1;
char fileName[13] = FILE_BASE_NAME "00.csv";
#define error(msg) sd.errorHalt(msg)

int Ppin = A4; // piezo pin 
int buttonPin = D9; // put button pin
bool buttonState;
const int arraySize = 4096;
int i;

long microstart;
long lastmicros;
float timeStamp;
float piezoData;
float array[2][arraySize];
int count;

void setup() {

  Serial.begin(9600);
  pinMode(Ppin, INPUT);
  pinMode(buttonPin, INPUT);
  pinMode(D7,OUTPUT);

  if (!sd.begin(chipSelect, SD_SCK_MHZ(50))) {
    sd.initErrorHalt();  
  }

  if (BASE_NAME_SIZE > 6) {
    Serial.println("FILE_BASE_NAME too long");
    while(1);
  }


  count = 0;
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
Serial.println("Press To Begin");
buttonState=digitalRead(buttonPin);
digitalWrite(D7,LOW);
while(!buttonState) {
  buttonState=digitalRead(buttonPin);
  Serial.print(".");
  delay(20);
} 
Serial.println(" ");
digitalWrite(D7,HIGH);
microstart=micros();
lastmicros = micros();

for (int i = 0; i < 4096; i++) {
  while((micros()-lastmicros) < 500);
    PiezoLogData();
    lastmicros=micros();
}
SDwrite();
count=0;
}

void SDwrite(){

float ave;

  Serial.printf("Starting data logging \n");
  while(sd.exists(fileName)){
    if(fileName[BASE_NAME_SIZE +1] != '9'){
      fileName[BASE_NAME_SIZE +1]++;
    }
    else if(fileName[BASE_NAME_SIZE] != '9'){
      fileName[BASE_NAME_SIZE +1] = '0';
      fileName[BASE_NAME_SIZE]++;
    }
    else{
      Serial.println("cant create file name");
      while(1);
    }
  }
  if(!file.open(fileName, O_WRONLY | O_CREAT | O_EXCL)){
    Serial.println("file.open");
  }
  Serial.printf("logging to %s \n",fileName);

  ave = findAve();
  file.printf("TimeStamp, Signal \n");
  for (int j=0;j<4096;j++) {
      file.printf("%0.8f , %0.2f \n",(array[0][j]),(array[1][j])/ave);
  }

  file.close();
  Serial.printf("done\n");
  delay(2000);
  Serial.printf("ready for next data log \n");
}


void PiezoLogData(){
  piezoData = analogRead(Ppin);
  array[0][count] = (micros()-microstart)/1000000.0;
  array[1][count] = piezoData;
  //Serial.printf("Time = %0.2f, signal = %0.2f \n",array[0][count],array[1][count]);
  count ++;
}

float findAve() {
  float total = 0;

  for (int j=0; j<4096;j++) {
    total = total+array[1][j];
  }
  
  return total/4096;
}
