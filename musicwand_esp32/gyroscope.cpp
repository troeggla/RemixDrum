#include "gyroscope.hpp"

void Gyroscope::begin() {
  // Setting MPU6050 accelerometer
  Wire.begin();
  Wire.beginTransmission(address); // Starting broadcast transmission with MPU address
  Wire.write(0X6B);

  // Reading the MPU6050 accelerometer
  Wire.write(0);
  Wire.endTransmission(true);
}

void Gyroscope::measure() {
  // Accelerometer MPU6050 logic
  Wire.beginTransmission(address);
  Wire.write(0X3B);
  Wire.endTransmission(false);
  Wire.requestFrom(address, 14, 1); // Reading MPU6050 data (14 bytes)

  delay(300); // Gyroscope reading time (300 ms)

  // Reading the gyroscope
  int gyro_X = Wire.read() << 8 | Wire.read();  //0x3B (GYRO_XOUT_H) & 0x3C (GYRO_XOUT_L)
  int gyro_Y = Wire.read() << 8 | Wire.read();  //0x3D (GYRO_YOUT_H) & 0x3E (GYRO_YOUT_L)
  int gyro_Z = Wire.read() << 8 | Wire.read();  //0x3F (GYRO_ZOUT_H) & 0x40 (GYRO_ZOUT_L)

  // Change the gyroscope's range (0º to 180º)
  this->angleX = map(gyro_X, GYRO_MIN, GYRO_MAX, 0, 180);
  this->angleY = map(gyro_Y, GYRO_MIN, GYRO_MAX, 0, 180);
  this->angleZ = map(gyro_Z, GYRO_MIN, GYRO_MAX, 0, 180);
}

int Gyroscope::getX() {
  return this->angleX;
}

int Gyroscope::getY() {
  return this->angleY;
}

int Gyroscope::getZ() {
  return this->angleZ;
}
