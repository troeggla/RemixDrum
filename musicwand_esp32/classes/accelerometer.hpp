#ifndef GRYOSCOPE_H
#define GRYOSCOPE_H

#include <Arduino.h>
#include <Wire.h>

#define ACCEL_MAX 65536 // Maximum value returned by the accelerometer

class Accelerometer {
  int address;

  int accelX = 0;
  int accelY = 0;
  int accelZ = 0;

  int gyroX = 0;
  int gyroY = 0;
  int gyroZ = 0;

public:
  Accelerometer(int address) : address(address) {};

  void begin();

  void measureAccel();
  int getAccelX();
  int getAccelY();
  int getAccelZ();

  void measureGyro();
  int getGyroX();
  int getGyroY();
  int getGyroZ();
};

#endif
