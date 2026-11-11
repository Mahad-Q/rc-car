#include <Arduino.h>
#include "controller.h"
#include "motors.h"

void setup() {
  Serial.begin(115200); // Starts communication between the ESP32 and computer at 115200 bits/sec (standardish rate)
  motorsBegin();
  initializeController();
}

void loop () {
  updateController();
  if (isControllerConnected()) {
    Serial.println("The Xbox Controller has successfully connected!");
  }
  else {
    Serial.println("Waiting for Xbox Controller...");
  }
  delay(500);
}



