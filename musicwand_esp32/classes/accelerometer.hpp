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

public:
  Accelerometer(int address) : address(address) {};

  void begin();
  void measure();
  int getX();
  int getY();
  int getZ();
};

#endif
