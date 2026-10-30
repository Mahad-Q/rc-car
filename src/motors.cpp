#include <Arduino.h>
#include "motors.h"

const int PIN_PWMA = 25; // Pulse Width Modulation	-> Controls motors speed
const int PIN_AIN1 = 24; // Controls motors direction
const int PIN_AIN2 = 23; // Controls motors direction

const int PIN_PWMB = 22; 
const int PIN_BIN1 = 21; 
const int PIN_BIN2 = 20; 

const int PIN_STBY = 4; // Turns the motor driver on/off

// Current motor speeds
int currentLeftSpeed = 0;
int currentRightSpeed = 0;

const int SPEED_STEP = 20;

void motorsBegin() {
    pinMode(25, OUTPUT);
    pinMode(24, OUTPUT);
    pinMode(23, OUTPUT);
    pinMode(22, OUTPUT);
    pinMode(21, OUTPUT);
    pinMode(20, OUTPUT);

    pinMode(4, OUTPUT);

    digitalWrite(PIN_STBY, HIGH);

    analogWrite(PIN_PWMA, 0);
    analogWrite(PIN_PWMB, 0);
}

// Move current speed toward target speed
int rampSpeed(int current, int target) {

    // Slow to zero before reversing direction
    if ((current > 0 && target < 0) ||(current < 0 && target > 0)) {

        if (current > 0) {
            return max(0, current - SPEED_STEP);
        }
        else {
            return min(0, current + SPEED_STEP);
        }
    }

    if (current < target) {
        return min(current + SPEED_STEP, target);
    }

    if (current > target) {
        return max(current - SPEED_STEP, target);
    }

    return current;
}

// Send speed to Motor A
void driveMotorA(int speed) {
    if (speed > 0) {
        digitalWrite(PIN_AIN1, HIGH);
        digitalWrite(PIN_AIN2, LOW);
    }
    else if (speed < 0) {
        digitalWrite(PIN_AIN1, LOW);
        digitalWrite(PIN_AIN2, HIGH);
    }
    else {
        digitalWrite(PIN_AIN1, LOW);
        digitalWrite(PIN_AIN2, LOW);
    }

    analogWrite(PIN_PWMA, abs(speed));
}

// Send speed to Motor B
void driveMotorB(int speed) {
    if (speed > 0) {
        digitalWrite(PIN_BIN1, HIGH);
        digitalWrite(PIN_BIN2, LOW);
    }
    else if (speed < 0) {
        digitalWrite(PIN_BIN1, LOW);
        digitalWrite(PIN_BIN2, HIGH);
    }
    else {
        digitalWrite(PIN_BIN1, LOW);
        digitalWrite(PIN_BIN2, LOW);
    }

    analogWrite(PIN_PWMB, abs(speed));
}

// Control both motors
void setDrive(int leftSpeed, int rightSpeed) {
    leftSpeed = constrain(leftSpeed, -255, 255);
    rightSpeed = constrain(rightSpeed, -255, 255);

    currentLeftSpeed = rampSpeed(currentLeftSpeed, leftSpeed);
    currentRightSpeed = rampSpeed(currentRightSpeed, rightSpeed);

    driveMotorA(currentLeftSpeed);
    driveMotorB(currentRightSpeed);
}

// Gradually slow both motors to zero
void slowDown() {
    setDrive(0, 0);
}

// Actively brake both motors
void brakeMotors() {
    currentLeftSpeed = 0;
    currentRightSpeed = 0;

    // Motor A short brake
    digitalWrite(PIN_AIN1, HIGH);
    digitalWrite(PIN_AIN2, HIGH);
    analogWrite(PIN_PWMA, 255);

    // Motor B short brake
    digitalWrite(PIN_BIN1, HIGH);
    digitalWrite(PIN_BIN2, HIGH);
    analogWrite(PIN_PWMB, 255);
}