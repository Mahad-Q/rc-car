#include <Arduino.h>
#include "motors.h"

const int PIN_PWMA = 25; // Pulse Width Modulation	-> Controls motors speed
const int PIN_AIN1 = 27; // Controls motors direction
const int PIN_AIN2 = 26; // Controls motors direction

const int PIN_PWMB = 32; 
const int PIN_BIN1 = 34; 
const int PIN_BIN2 = 35; 

const int PIN_STBY = 33; // Turns the motor driver on/off

// Current motor speeds
int currentLeftSpeed = 0;
int currentRightSpeed = 0;

const int SPEED_STEP = 20; // Just a faster way of how much I want the motors to accelerate/deacclerate by

void motorsBegin() {
    pinMode(25, OUTPUT);
    pinMode(27, OUTPUT);
    pinMode(26, OUTPUT);
    pinMode(32, OUTPUT);
    pinMode(34, OUTPUT);
    pinMode(35, OUTPUT);

    pinMode(33, OUTPUT);

    digitalWrite(PIN_STBY, HIGH);

    analogWrite(PIN_PWMA, 0);
    analogWrite(PIN_PWMB, 0);
}

// Move current speed toward target speed
int rampSpeed(int current, int target) {

    // Slow to zero and then reversing direction
    if ((current > 0 && target < 0) ||(current < 0 && target > 0)) {

        // if the motor is currently going forward, decrease its speed by 20 until it stops
        if (current > 0) {
            return max(0, current - SPEED_STEP);
        }
        // if the motor is currently going backwards, increase its speed by 20 until it stops
        else {
            return min(0, current + SPEED_STEP);
        }
    }

    // if the current speed is slower than the target speed, increase the speed by 20 until it reaches target
    if (current < target) {
        return min(current + SPEED_STEP, target);
    }

    // if the current speed is faster than the target speed, decrease the speed by 20 until it reaches target
    if (current > target) {
        return max(current - SPEED_STEP, target);
    }

    // If current already equals target, no speed change is needed.
    return current;
}

// Send speed to Motor A
void driveMotorA(int speed) {
    // Positive speed: Set the motor driver inputs to spin Motor A forward.
    if (speed > 0) {
        digitalWrite(PIN_AIN1, HIGH); 
        digitalWrite(PIN_AIN2, LOW); 
    }
    // Negative  speed: Reverse the input signals to spin Motor A backward.
    else if (speed < 0) {
        digitalWrite(PIN_AIN1, LOW); //left motor goes slow
        digitalWrite(PIN_AIN2, HIGH); //right motor goes fast
    }
    // Zero speed: Disable active drive so the motor can coast.
    else {
        digitalWrite(PIN_AIN1, LOW); // both motors stop
        digitalWrite(PIN_AIN2, LOW);
    }
    // The absolute value removes the negative sign because motor direction
    // is already controlled separately using AIN1 and AIN2.
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

// Control both motors using their requested left and right speeds.
void setDrive(int leftSpeed, int rightSpeed) {
    // Limit the requested left motor speed to the range of -255 to 255
    leftSpeed = constrain(leftSpeed, -255, 255);
    rightSpeed = constrain(rightSpeed, -255, 255);
    // Gradually adjust the current left motor speed toward its target speed
    currentLeftSpeed = rampSpeed(currentLeftSpeed, leftSpeed);
    currentRightSpeed = rampSpeed(currentRightSpeed, rightSpeed);
     // Apply the updated speed and direction to the left motor (Motor A)
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

    // Set both direction pins HIGH, telling the TB6612FNG to connect both motor output terminals together, creating a short-brake condition that opposesthe motor's rotation. 
    // Set PWM to 255 (100%) to keep the braking output continuously enabled 
    digitalWrite(PIN_AIN1, HIGH);
    digitalWrite(PIN_AIN2, HIGH);
    analogWrite(PIN_PWMA, 255);

    // Motor B short brake
    digitalWrite(PIN_BIN1, HIGH);
    digitalWrite(PIN_BIN2, HIGH);
    analogWrite(PIN_PWMB, 255);
}