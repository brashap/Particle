/*
 * Project ASCIItoBITs
 * Description:
 * Author:
 * Date:
 */

SYSTEM_MODE(SEMI_AUTOMATIC);
SYSTEM_THREAD(ENABLED);

const int laserPin = D7;
const int buttonPin = D5;
const int extraButtonPin = D6;

unsigned int zeroTime = 100;
unsigned int oneTime = 1000;
unsigned int offDelay = 500;
unsigned int zeroCurrentTime;
unsigned int zeroLastTime;
unsigned int oneCurrentTime;
unsigned int oneLastTime;

bool buttonState;
bool extraButtonState;

String temp;
char temp_array[20];
float testTemp = 3.141592653589793238462643383279;
byte data[8];
int i;
int u;
int n;

void setup() {

  Serial.begin(9600);

  pinMode(laserPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLDOWN);
  pinMode(extraButtonPin, INPUT_PULLDOWN);
  pinMode(A1, OUTPUT); //used for testing 
  pinMode(D7, OUTPUT); //used for testing
}

void loop() {

  temp = String(testTemp);

  temp.toCharArray(temp_array, 20);
  for(n = 0; n < 8; n++) {
    for(i = 0; i < 8; i++){
      data[i] = temp_array[n] >> i & 0x01;
      Serial.printf("temp_array: %x data: %i i: %i n: %i\n", temp_array[n], data[i], i, n);
      delay(1000);
    }
    sendAscii(data);
  } 
  
}

void sendAscii(byte send_array[8]){ 
      // send_array[i] = 0 == 1;

      if(send_array[i] == 0){ //laser 
      beamZero(); 
      Serial.printf("Zero");
      }
      else if(send_array[i] == 1){
      beamOne();
      Serial.printf("One");
      }
  }
  
void longPressStart1() {

  Serial.println("Button 1 longPress start");
  analogWrite(D7, 200);
  Serial.printf("Temperature: %f\n", temp);
} 

void longPressStop1() {

  Serial.println("Button 1 longPress stop");
  analogWrite(D7, 0);

}

void beamZero() {

  // Serial.printf("Array value is ZERO\n");
  digitalWrite(laserPin, HIGH);
  //Serial.printf("ZERO\n");
  delay(zeroTime);
  digitalWrite(laserPin, LOW);
  delay(offDelay);

}

void beamOne() {

  //Serial.printf("Array value is ONE\n");
  digitalWrite(laserPin, HIGH);
  //Serial.printf("ONE\n");
  delay(oneTime);
  digitalWrite(laserPin, LOW);
  delay(offDelay);
}