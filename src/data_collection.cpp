/*
#include <Arduino.h>
#include <Wire.h>
#include <BH1750.h>
#include <Adafruit_BMP280.h>
#include <TinyGPSPlus.h>
#include <iostream> 
#include <cmath>

BH1750 lightMeter;
Adafruit_BMP280 bmp;
TinyGPSPlus gps;
void data_setup() {
  Serial.begin(115200);
  Wire.begin(21, 22); // Initialize I2C with SDA on pin 21 and SCL on pin 22

  if (!lightMeter.begin()) {
    Serial.println("BH1750 not found");
  }
  if (!bmp.begin(0x76)) {
    Serial.println("BMP280 not found");
  }
}

void data_loop() {
  Serial.print(lightMeter.readLightLevel());
  Serial.print(", ");
  Serial.print(bmp.readTemperature());
  Serial.print(", ");
  Serial.println(bmp.readPressure() / 100.0);
  delay(1000);
}

*/

#include <Arduino.h>
#include <Wire.h>
#include <BH1750.h>

BH1750 lightMeter;

void data_setup() {
  Serial.begin(115200);
  Wire.begin(21, 22); //initialize I2C with SDA on pin 21 and SCL on pin 22
  if (!lightMeter.begin()) Serial.println("BH1750 not found");
}

void data_loop() {
  Serial.println(lightMeter.readLightLevel());
  delay(1000);
}