#ifndef IMU_H
#define IMU_H

#include <Arduino.h>
#include <Wire.h>

#define IMU_MAX 65536 // Maximum value returned by the accelerometer

class IMU {
  int address;

  int accelX = 0;
  int accelY = 0;
  int accelZ = 0;

  int gyroX = 0;
  int gyroY = 0;
  int gyroZ = 0;

public:
  /**
   * @brief Construct a new IMU object with the given hardware address.
   *
   * @param address Hardware address of the IMU
   */
  IMU(int address) : address(address) {};

  /**
   * @brief Initialise IMU module
   */
  void begin();

  /**
   * @brief Retrieve accelerator measurements from IMU module
   */
  void measureAccel();

  /**
   * @brief Get the acceleration along the x-axis.
   *
   * @return int Acceleration along x-axis
   */
  int getAccelX();

  /**
   * @brief Get the acceleration along the y-axis.
   *
   * @return int Acceleration along y-axis
   */
  int getAccelY();

  /**
   * @brief Get the acceleration along the z-axis.
   *
   * @return int Acceleration along z-axis
   */
  int getAccelZ();

  /**
   * @brief Retrieve gyroscope measurements from IMU module
   */
  void measureGyro();

  /**
   * @brief Get the angular rotation around the x-axis.
   *
   * @return int Angular rotation around x-axis
   */
  int getGyroX();

  /**
   * @brief Get the angular rotation around the y-axis.
   *
   * @return int Angular rotation around y-axis
   */
  int getGyroY();

  /**
   * @brief Get the angular rotation around the z-axis.
   *
   * @return int Angular rotation around z-axis
   */
  int getGyroZ();
};

#endif
