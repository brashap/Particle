/*
 * Project MQ09
 * Description: Sample Code for Using NCD.io MQ09
 * Author: Brian Rashap
 * Date: 21-APR-2020
 */


// ADC121C_MQ9 I2C address is 0x50(80)
#define Addr 0x50

int raw_adc;
double ppm;


void setup()
{
  Serial.begin(9600);

  // Set variable
  Particle.variable("i2cdevice", "ADC121C_MQ9");
  Particle.variable("PPM", ppm);

  // Initialise I2C communication as MASTER
  Wire.begin();
}

void loop()
{
unsigned int data[2];
  
  // Start I2C transmission
  Wire.beginTransmission(Addr);
  // Select data register
  Wire.write(0x00);
  // Stop I2C transmission
  Wire.endTransmission();

  // Request 2 bytes of data
  Wire.requestFrom(Addr, 2);

  // Read 2 bytes of data
  // raw_adc msb, raw_adc lsb
  if (Wire.available() == 2)
  {
    data[0] = Wire.read();
    data[1] = Wire.read();
  }
  delay(300);

  // Convert the data to 12-bits
  raw_adc = ((data[0] & 0x0F) * 256) + data[1];
  ppm = (1000 / 4096.0) * raw_adc + 10;

  // Output data to dashboard
  Particle.publish("Carbon Monoxide Concentration : ", String(ppm));
  Serial.printf("CO conc = %0.2f \n",ppm);
  delay(60000);
}
