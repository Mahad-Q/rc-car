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

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);
  delay(200);
  while (!light_read.begin(BH1750::CONTINUOUS_HIGH_RES_MODE)) {
    Serial.println("gy-302 not found, retrying...");
    delay(500);
  }
  Serial.println("gy-302 ready");
}


void loop() {
  float temp  = readTemp();
  float lux   = light_read.readLightLevel();
  int   sound = readSound();

  Serial.printf("%.2f,%.1f,%d\n", temp, lux, sound);
  delay(950);
}
