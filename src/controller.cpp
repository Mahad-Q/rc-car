#include <Arduino.h>
#include "controller.h"
#include "motors.h"
#include <BLEGamepadClient.h>

XboxController controller;
XboxControlsState controllerState;

void initializeController() {
    controller.begin();
}

void updateController() {
    if (isControllerConnected()) {

        // Read the latest Xbox controller inputs.
        controller.read(&controllerState);

        Serial.print("Left Stick X: ");
        Serial.print(controllerState.leftStickX);

        Serial.print(" | Right Trigger: ");
        Serial.print(controllerState.rightTrigger);

        Serial.print(" | Left Trigger: ");
        Serial.print(controllerState.leftTrigger);

        Serial.print(" | B Button: ");
        Serial.println(controllerState.buttonB);

        // Press B to brake immediately.
        if (controllerState.buttonB) {
            brakeMotors();
        }
        else {
            // Read the right and left triggers.
            float rtValue = controllerState.rightTrigger;
            float ltValue = controllerState.leftTrigger;

            // Apply trigger deadzones.
            if (rtValue < 0.05f) rtValue = 0.0f;
            if (ltValue < 0.05f) ltValue = 0.0f;

            // Convert trigger values from 0-1 to motor speeds from 0-255.
            int rtSpeed = rtValue * 255;
            int ltSpeed = ltValue * 255;

            // Calculate forward and reverse throttle.
            int throttle = rtSpeed - ltSpeed;

            // Read the horizontal left joystick axis.
            float steeringValue = controllerState.leftStickX;

            // Apply steering deadzone.
            if (abs(steeringValue) < 0.05f) {
                steeringValue = 0.0f;
            }

            // Convert steering from -1 to 1 into -255 to 255.
            int steering = steeringValue * 255;

            // Calculate individual motor speeds.
            int leftSpeed = constrain(throttle + steering, -255, 255);
            int rightSpeed = constrain(throttle - steering, -255, 255);

            // Send the calculated speeds to the motors.
            setDrive(leftSpeed, rightSpeed);
        }
    }
    else {
        // Stop the motors if the controller disconnects.
        brakeMotors();
    }
}

bool isControllerConnected() {
    return controller.isConnected();
}