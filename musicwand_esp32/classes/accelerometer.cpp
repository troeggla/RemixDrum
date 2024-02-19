#include "accelerometer.hpp"

void Accelerometer::begin() {
  // Setting MPU6050 accelerometer
  Wire.begin();
  Wire.beginTransmission(address);
  Wire.write(0x6B);

  // Write 0 to register 0x6B to reset the IMU
  Wire.write(0x00);
  Wire.endTransmission(true);
}

void Accelerometer::measure() {
  // Accelerometer MPU6050 logic
  Wire.beginTransmission(address);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(address, 6, 1); // Reading MPU6050 data (6 bytes)

  delay(300); // Accelerometer reading time (300 ms)

  // Reading the gyroscope
  int accel_X = Wire.read() << 8 | Wire.read();  //0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  int accel_Y = Wire.read() << 8 | Wire.read();  //0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  int accel_Z = Wire.read() << 8 | Wire.read();  //0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)

  // Change the gyroscope's range (0º to 180º)
  this->accelX = map(accel_X, 0, ACCEL_MAX, 0, 180);
  this->accelY = map(accel_Y, 0, ACCEL_MAX, 0, 180);
  this->accelZ = map(accel_Z, 0, ACCEL_MAX, 0, 180);
}

int Accelerometer::getX() {
  return this->accelX;
}

int Accelerometer::getY() {
  return this->accelY;
}

int Accelerometer::getZ() {
  return this->accelZ;
}
