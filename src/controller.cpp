#include <Arduino.h>
#include "controller.h"
#include <BLEGamepadClient.h>

XboxController controller;
XboxControlsState controllerState; // Stores the latest Xbox controller inputs (joystick positions and button states) so other parts of the program can use them.

void initializeController () {
    controller.begin(); // Initializes the BLE connection so the ESP32 can communicate with the Xbox controller using begin() from the library

}


void updateController() {
    if (isControllerConnected()) {
        controller.read(&controllerState); // controller.read() is from the libray which reads the latest controller input, we change the value of state in the funciton so that it can be called within the specific variables (e.g state.leftstick)
    }

}

bool isControllerConnected () {
    return controller.isConnected(); // isConnected() is  found within the BLE library
}