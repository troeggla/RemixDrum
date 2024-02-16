/*
Music Wand
Created by: Rômulo Vieira, Célio Albuquerque & Débora Muchaluat-Saade
Fluminense Federal University (UFF) - Brazil
GNU General Public License v3

Buy me a coffee --> paypal: romulo_vieira96@yahoo.com.br
*/

// Include Libraries
#include <Wire.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <OSCMessage.h>

#include "gyroscope.hpp"
#include "capacitive_touch_pad.hpp"

// Constants
#define TOUCH_PIN D0 // Touch sensor pin (D0 pin on ESP32)
#define MPU_ADDRESS 0x68 // Address on the NOdeMCU v3 board for the MPU6050 accelerometer

const IPAddress outIp(255,255,255,255); // Client computer IP
const unsigned int outPort = 9999; // Client computer port for Pure Data
const unsigned int outPort2 = 7777; // Client computer port for Processing
const unsigned int localPort = 2390; // Local port to listen for OSC packets

// SSID and password for WiFi
char ssid[] = "Romulo"; // EDIT: Network name
char pass[] = "romulo182"; // EDIT: Network password

// UDP socket
WiFiUDP socket;

// Gyroscope
Gyroscope gyro(MPU_ADDRESS);
// Capacitive touch pad
CapacitiveTouchPad touchPad(TOUCH_PIN);

/**
 * Sends an OSC message with the given value and route to the given IP and port.
 * Messages are sent via UDP.
 *
 * @param ip The IP address of the host to send the message to
 * @param port Port to send the message to
 * @param route OSC route of the message
 * @param value Value to put into the message
*/
void sendOSCMessage(IPAddress ip, unsigned int port, const char route[], int32_t value) {
  // Init message and add value
  OSCMessage message(route);
  message.add(value);

  // Send message via UDP
  socket.beginPacket(ip, port);
  message.send(socket);
  socket.endPacket();

  // Clear message
  message.empty();
}

void setup() {
  // Baud Rate
  Serial.begin(9600);

  // Connecting to Wi-Fi Network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  Serial.println("Starting UDP");
  socket.begin(localPort);
  Serial.print("Local port: ");
  Serial.println(localPort);

  // Initialise gyroscope
  gyro.begin();
}

void loop() {
  // Touch sensor logic
  int padIsTouched = touchPad.isTouched(); // Reading the touch sensor
  Serial.println(padIsTouched); // Print touch sensor in serial monitor
  delay(50); // Touch sensor reading time (50 ms)

  // Get reading from gyroscope
  gyro.measure();

  // Send X axis to serial monitor
  Serial.print(" | GyX = "); Serial.print(gyro.getX());
  // Send Y axis to serial monitor
  Serial.print(" | GyY = "); Serial.print(gyro.getY());
  // Send Z axis to serial monitor
  Serial.print(" | GyZ = "); Serial.println(gyro.getZ());
  delay(300); // Gyroscope reading time (300 ms)

  // Send touch sensor message to the client with OSC protocol
  sendOSCMessage(outIp, outPort, "/value", padIsTouched);
  delay(500);

  // Sending accelerometer X-axis message to Pure Data
  sendOSCMessage(outIp, outPort, "/gyx", gyro.getX());
  delay(10);

  // Sending accelerometer X-axis message to Processing
  sendOSCMessage(outIp, outPort2, "/gyx", gyro.getX());
  delay(10);

  // Sending accelerometer Y-axis message to Pure Data
  sendOSCMessage(outIp, outPort, "/gyy", gyro.getY());
  delay(10);

  // Sending accelerometer Y-axis message to Processing
  sendOSCMessage(outIp, outPort2, "/gyy", gyro.getY());
  delay(10);

  // Sending accelerometer Z axis message to Pure Data
  sendOSCMessage(outIp, outPort, "/gyz", gyro.getZ());
  delay(100);
}
