#include <Arduino.h>
#include <Wire.h>

void data_setup();
void data_loop();

void setup() {
  data_setup();
}

void loop() {
  data_loop();
}
/*
const int LED_PIN = 2;

void setup() 
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_PIN, HIGH);
  Serial.println("LED on");
  delay(500);
  digitalWrite(LED_PIN, LOW);
  Serial.println("LED off");
  delay(500);
}
  */



