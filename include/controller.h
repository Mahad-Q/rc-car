#pragma once
#include <BLEGamepadClient.h>

extern XboxControlsState controllerState; // Allows other files to access state for input readings from joysticks and buttons

void initializeController();

void updateController();

bool isControllerConnected();