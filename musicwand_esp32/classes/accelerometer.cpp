#include "accelerometer.hpp"

void Accelerometer::begin() {
  // Setting MPU6050 accelerometer
  Wire.begin();
  Wire.beginTransmission(address);
  Wire.write(0x6B);

  // Reset the IMU
  Wire.write(0x00);
  Wire.endTransmission(true);
}

void Accelerometer::measureAccel() {
  // Accelerometer MPU6050 logic
  Wire.beginTransmission(address);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(address, 6, 1); // Reading MPU6050 data (6 bytes)

  // Reading the accelerometer
  int accel_X = Wire.read() << 8 | Wire.read();  //0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  int accel_Y = Wire.read() << 8 | Wire.read();  //0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  int accel_Z = Wire.read() << 8 | Wire.read();  //0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)

  // Change the accelerometer's range (0º to 180º)
  this->accelX = map(accel_X, 0, ACCEL_MAX, 0, 180);
  this->accelY = map(accel_Y, 0, ACCEL_MAX, 0, 180);
  this->accelZ = map(accel_Z, 0, ACCEL_MAX, 0, 180);
}

int Accelerometer::getAccelX() {
  return this->accelX;
}

int Accelerometer::getAccelY() {
  return this->accelY;
}

int Accelerometer::getAccelZ() {
  return this->accelZ;
}

void Accelerometer::measureGyro() {
  // Gyroscope MPU6050 logic
  Wire.beginTransmission(address);
  Wire.write(0x43);
  Wire.endTransmission(false);
  Wire.requestFrom(address, 6, 1); // Reading MPU6050 data (6 bytes)

  // Reading the gyroscope
  int gyro_X = Wire.read() << 8 | Wire.read();  //0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  int gyro_Y = Wire.read() << 8 | Wire.read();  //0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  int gyro_Z = Wire.read() << 8 | Wire.read();  //0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)

  // Change the gyroscope's range (0º to 180º)
  this->gyroX = map(gyro_X, 0, ACCEL_MAX, 0, 180);
  this->gyroY = map(gyro_Y, 0, ACCEL_MAX, 0, 180);
  this->gyroZ = map(gyro_Z, 0, ACCEL_MAX, 0, 180);
}

int Accelerometer::getGyroX() {
  return this->gyroX;
}

int Accelerometer::getGyroY() {
  return this->gyroY;
}

int Accelerometer::getGyroZ() {
  return this->gyroZ;
}
