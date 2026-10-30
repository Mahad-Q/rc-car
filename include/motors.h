#pragma once
#include <Arduino.h>

void motorsBegin();

void setDrive(int leftSpeed, int rightSpeed);

void slowDown();

void brakeMotors();