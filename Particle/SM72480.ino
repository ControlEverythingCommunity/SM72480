// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// SM72480
// This code is designed to work with the ADC121C021_SM72480_I2CS I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/products

#include <application.h>
#include <spark_wiring_i2c.h>

// SM72480 I2C address is 0x50(80)
#define Addr 0x50

int raw_adc = 0;
void setup()
{
  // Set variable
  Particle.variable("i2cdevice", "SM72480");
  Particle.variable("raw_adc", raw_adc);
  
  // Initialise I2C communication as Master
  Wire.begin();
  // Initialise serial communication, set baud rate = 9600
  Serial.begin(9600);

  // Start I2C transmission
  Wire.beginTransmission(Addr);
  // Select configuration register
  Wire.write(0x02);
  // Automatic conversion mode enabled
  Wire.write(0x20);
  // Stop I2C transmission
  Wire.endTransmission();
  delay(300);
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

  // Request 2 byte of data
  Wire.requestFrom(Addr, 2);

  // Read 2 byte of data
  // raw_adc msb, raw_adc lsb
  if (Wire.available() == 2)
  {
    data[0] = Wire.read();
    data[1] = Wire.read();
  }

  // Convert the data to 12-bits
  int raw_adc = (data[0] & 0x0F) * 256 + data[1];

  // Output data to dashboard
  Particle.publish("Digital value of analog input  : ", String(raw_adc));
  delay(500);
}
