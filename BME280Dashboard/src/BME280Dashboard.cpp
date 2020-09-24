/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#line 1 "c:/Users/IoTPa/Documents/Particle/BME280Dashboard/src/BME280Dashboard.ino"
/*
 * Project BME280Dashboard
 * Description: BME280 Data to Adafruit IO cloud
 * Note: As with all I2C projects, I include a I2C Scan function to 
 *       validate that the I2C connections are working
 * Author: Brian Rashap
 * Date: 11/7/2019
 */

#include <Adafruit_MQTT.h>


#include "Adafruit_MQTT/Adafruit_MQTT.h"
#include "Adafruit_MQTT/Adafruit_MQTT_SPARK.h"

/************************* Adafruit.io Setup *********************************/
#define AIO_SERVER      "io.adafruit.com" 
#define AIO_SERVERPORT  1883                   // use 1883 or 8883 for SSL 
#define AIO_USERNAME  "rashap"
#define AIO_KEY       "598169fa3ba94636941a330976e42e2c"

/************ Global State (you don't need to change this!) ******************/ 
TCPClient TheClient; 

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details. 
Adafruit_MQTT_SPARK mqtt(&TheClient,AIO_SERVER,AIO_SERVERPORT,AIO_USERNAME,AIO_KEY); 

/****************************** Feeds ***************************************/ 
// Notice MQTT paths for AIO follow the form: <username>/feeds/<feedname> 

Adafruit_MQTT_Publish temp = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/Home_Temperature");
Adafruit_MQTT_Publish press = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/Pressure");
Adafruit_MQTT_Publish rh = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/Relative_Humidity");

/*************************** Setup BME280 ***********************************/

#include "Particle.h"
void setup();
void loop();
void I2CScan();
void printValues();
#line 38 "c:/Users/IoTPa/Documents/Particle/BME280Dashboard/src/BME280Dashboard.ino"
#include "Adafruit_Sensor.h"
#include "Adafruit_BME280.h"

Adafruit_BME280 bme; 

unsigned long delayTime;
#define SEALEVELPRESSURE_HPA (1013.25)

/*************************** Sketch Code ************************************/
float temperature;
float pressure;
float humidity;

void setup() {
    Wire.begin();

    Serial.begin(115200);
    while(!Serial);         // wait for serial to start running
    Serial.println("\nI2C Scanner");

    unsigned status;

    status = bme.begin();
    if (!status) {
        Serial.println("Could not find a valid BME280 sensor, check writing");
        while (1);
    }
    delayTime = 1000;
    I2CScan();
}

void loop()
{
    printValues();
    temperature = bme.readTemperature()*1.6+32.0;
    pressure = bme.readPressure() / 100.0;
    humidity = bme.readHumidity();

    Serial.println("----------------Data to Publish-----------------");
    Serial.println(temperature);
    Serial.println(pressure);
    Serial.println(humidity);
    Serial.println("------------------End Publish-------------------");


if(mqtt.Update()) {
    temp.publish(temperature);
    press.publish(pressure);
    rh.publish(humidity);
    }   

delay(10000);
}

void I2CScan()
{
    byte error, address;
    int nDevices;

    Serial.println("--------------------------");
    Serial.println("-Scanning for I2C Devices-");
    Serial.println("--------------------------");
    delay(5000);

    nDevices = 0;
    for(address = 1; address < 127; address++)
    {
        Wire.beginTransmission(address);
        error = Wire.endTransmission();

        if (error == 0)
        {
            Serial.print("I2C device found at address 0x");
            if (address<16)
                Serial.print("0");
            Serial.print(address,HEX);
            Serial.println("  !");

            nDevices++;
        }
        else if (error==4)
        {   
            Serial.print("Unknown error at address 0x");
            if (address<16)
                Serial.print("0");
            Serial.print(address,HEX);
        }
    }
    if (nDevices == 0)
        Serial.println("No I2C devices found\n");
    else
        Serial.println("Done\n");
    

}

void printValues() 
{
    Serial.print("Temperature = ");
    Serial.print(bme.readTemperature());
    Serial.println(" *C");

    Serial.print("Pressure = ");
    Serial.print(bme.readPressure() / 100.0F);
    Serial.println(" hPa");

    Serial.print("Approx. Altitude = ");
    Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
    Serial.println(" m");

    Serial.print("Humidity = ");
    Serial.print(bme.readHumidity());
    Serial.println(" %");

    Serial.println(); 
}