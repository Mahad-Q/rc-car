/*
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_BME280.h>
#include <Adafruit_BMP280.h>

Adafruit_BME280 bme;
Adafruit_BMP280 bmp;


void data_setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);
  delay(200);

  if (!bmp.begin(0x76)) {
    Serial.println("bmp not found at 0x76, trying 0x77...");
    if (!bmp.begin(0x77)) {
      Serial.println("bmp not found");
      while (true) delay(1000);
    }
  }
  Serial.println("bmp ready");
}


void data_loop() {
  Serial.print("Temp: ");
  Serial.print(bmp.readTemperature());
  Serial.print(" C | Pressure: ");
  Serial.print(bmp.readPressure() / 100.0);
  Serial.print(" hPa | Humidity: ");
  delay(1000);
}
*/

/*
#include <Arduino.h>
#include <Wire.h>
#include <BH1750.h>

BH1750 light_read(0x23);

void data_setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);
  delay(200);
  while (!light_read.begin(BH1750::CONTINUOUS_HIGH_RES_MODE)) {
    Serial.println("gy-302 not found, retrying...");
    delay(500);
  }
  Serial.println("gy-302 ready");
}

void data_loop() {
  Serial.print("Light Level: ");
  Serial.println(light_read.readLightLevel());
  delay(500);
}
*/
/*
#include <Arduino.h>
#include <Wire.h>

void data_setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);
  delay(1000);
  Serial.println("Scanning...");
}

void data_loop() {
  int found = 0;
  for (byte addr = 1; addr < 127; addr++) {
    Wire.beginTransmission(addr);
    if (Wire.endTransmission() == 0) {
      Serial.print("Found device at 0x");
      Serial.println(addr, HEX);
      found++;
    }
  }
  if (found == 0) Serial.println("No devices found");
  Serial.println("---");
  delay (3000);
}
*/

/*
#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);  // address, columns, rows

void data_setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Hello World");
}

void data_loop() {
}
*/

#include <Arduino.h>
#include <Wire.h>
#include <BH1750.h>
#include <math.h>

const int TEMP_PIN  = 34;
const int SOUND_PIN = 35;
const float ADC_MAX = 4095.0;

BH1750 light_read(0x23);


const float B  = 4275.0;
const float R0 = 100000.0;

float readTemp() {
  float raw = analogRead(TEMP_PIN);
  float R = (ADC_MAX / raw - 1.0) * R0;
  return 1.0 / (log(R / R0) / B + 1.0 / 298.15) - 273.15;
}

int readSound() {
  int lo = 9999, hi = 0;
  unsigned long start = millis();
  while (millis() - start < 50) {
    int v = analogRead(SOUND_PIN);
    if (v < lo) lo = v;
    if (v > hi) hi = v;
  }
  return hi - lo;
}

void data_setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);
  delay(200);
  while (!light_read.begin(BH1750::CONTINUOUS_HIGH_RES_MODE)) {
    Serial.println("gy-302 not found, retrying...");
    delay(500);
  }
  Serial.println("gy-302 ready");
}


void data_loop() {
  float temp  = readTemp();
  float lux   = light_read.readLightLevel();
  int   sound = readSound();

  Serial.printf("%.2f,%.1f,%d\n", temp, lux, sound);
  delay(950);
}
