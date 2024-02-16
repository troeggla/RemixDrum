#ifndef GRYOSCOPE_H
#define GRYOSCOPE_H

#include <Arduino.h>
#include <Wire.h>

#define GYRO_MIN 0 // Minimum value returned by the gyroscope
#define GYRO_MAX 65536 // Maximum value returned by the gyroscope

class Gyroscope {
  int address;
  int angleX = 0;
  int angleY = 0;
  int angleZ = 0;

public:
  Gyroscope(int address) : address(address) {};

  void begin();
  void measure();
  int getX();
  int getY();
  int getZ();
};

#endif
