/*
Music Wand
Created by: Rômulo Vieira, Célio Albuquerque & Débora Muchaluat-Saade
Fluminense Federal University (UFF) - Brazil
Updated by: Thomas Röggla
Centrum Wiskunde & Informatica (CWI) - Netherlands
GNU General Public License v3

Buy me a coffee --> paypal: romulo_vieira96@yahoo.com.br
*/
#include <WiFi.h>

#include "classes/capacitive_touch_pad.hpp"
#include "classes/imu.hpp"
#include "classes/osc_endpoint.hpp"

// SSID and password for WiFi
#define WIFI_SSID "Romulo" // EDIT: Network name
#define WIFI_PASS "romulo182" // EDIT: Network password

// Constants
#define TOUCH_PIN D0 // Touch sensor pin (D0 pin on ESP32)
#define MPU_ADDRESS 0x68 // I2C address for the MPU6050 accelerometer

// Port definitions
#define PURE_DATA_PORT 9999
#define PROCESSING_PORT 7777
#define LOCAL_PORT 2390

// UDP socket
WiFiUDP socket;

// OSC endpoints
OSCEndpoint pureDataEndPoint(socket, PURE_DATA_PORT);
OSCEndpoint processingEndPoint(socket, PROCESSING_PORT);

// IMU
IMU imu(MPU_ADDRESS);

// Capacitive touch pad
CapacitiveTouchPad touchPad(TOUCH_PIN);

void setup() {
  // Baud Rate
  Serial.begin(115200);

  // Connecting to Wi-Fi Network
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  Serial.println(" ");

  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();

  Serial.println("WiFi connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  Serial.println("Starting UDP");
  socket.begin(LOCAL_PORT);

  // Initialise IMU
  imu.begin();
}

void loop() {
  // Touch sensor logic
  int padIsTouched = touchPad.isTouched(); // Reading the touch sensor
  Serial.print(padIsTouched); // Print touch sensor in serial monitor

  // Get reading from accelerometer
  imu.measureAccel();

  // Send X axis to serial monitor
  Serial.print(" | GyX = ");
  Serial.print(imu.getAccelX());
  // Send Y axis to serial monitor
  Serial.print(" | GyY = ");
  Serial.print(imu.getAccelY());
  // Send Z axis to serial monitor
  Serial.print(" | GyZ = ");
  Serial.println(imu.getAccelZ());

  // Send touch sensor message to the client with OSC protocol
  pureDataEndPoint.sendMessage("/value", padIsTouched);

  // Sending accelerometer X-axis message to Pure Data
  pureDataEndPoint.sendMessage("/gyx", imu.getAccelX());
  // Sending accelerometer X-axis message to Processing
  processingEndPoint.sendMessage("/gyx", imu.getAccelX());

  // Sending accelerometer Y-axis message to Pure Data
  pureDataEndPoint.sendMessage("/gyy", imu.getAccelY());
  // Sending accelerometer Y-axis message to Processing
  processingEndPoint.sendMessage("/gyy", imu.getAccelY());

  // Sending accelerometer Z axis message to Pure Data
  pureDataEndPoint.sendMessage("/gyz", imu.getAccelZ());

  delay(100);
}
