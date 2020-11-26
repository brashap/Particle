/*
 * Project YouGotMail
 * Description: Raise a Flag on 3D printed mailbox whenever new mail arrives in Outlook account
 * Author: Brian Rashap
 * Date: 11-NOV-2020
 */

#include <Adafruit_MQTT.h>

#include "Adafruit_MQTT/Adafruit_MQTT.h" 
#include "Adafruit_MQTT/Adafruit_MQTT_SPARK.h" 
#include "Adafruit_MQTT/Adafruit_MQTT.h" 

#include "credentials.h"

/************ Global State (you don't need to change this!) ***   ***************/ 
TCPClient TheClient; 

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details. 
Adafruit_MQTT_SPARK mqtt(&TheClient,AIO_SERVER,AIO_SERVERPORT,AIO_USERNAME,AIO_KEY); 

/****************************** Feeds ***************************************/ 
// Setup Feeds to publish or subscribe 
// Notice MQTT paths for AIO follow the form: <username>/feeds/<feedname> 
Adafruit_MQTT_Subscribe gotmail = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/gmail"); 

/************Servo Object************/
Servo flagServo;

/************Declare Variables*************/
unsigned long last;
unsigned long lastTime;

void setup() {
  Serial.begin(9600);
  delay(100); //wait for Serial Monitor to startup

  // Initialize Flag
  flagServo.attach(A3);
  flagServo.write(5);
  flagServo.write(90);
  delay(2000);
  flagServo.write(5);
  // Setup MQTT subscription for gmail feed.
  mqtt.subscribe(&gotmail);
  pinMode(D7, OUTPUT);
  Serial.printf("Ready to Get Mail \n");
}

void loop() {
  MQTT_connect();

  if ((millis()-last)>120000) {
      Serial.printf("Pinging MQTT \n");
      if(! mqtt.ping()) {
        Serial.printf("Disconnecting \n");
        mqtt.disconnect();
      }
      last = millis();
  }
 
  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(10000))) {
    if (subscription == &gotmail) {
      Serial.printf("You Got Mail \n");
      digitalWrite(D7, HIGH);
      flagServo.write(90);
      delay(20000);
      digitalWrite(D7, LOW);
      flagServo.write(5);
    }
  }
}

// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
void MQTT_connect() {
  int8_t ret;
 
  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }
 
  Serial.print("Connecting to MQTT... ");
 
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
  }
  Serial.println("MQTT Connected!");
}