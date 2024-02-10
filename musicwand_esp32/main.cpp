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

// Constants
#define TOUCH_THRESHOLD 150000
#define TOUCH_PIN 14 // Touch sensor pin (D5 pin on ESP8266)

const int MPU = 0x68; // Address on the NOdeMCU v3 board for the MPU6050 accelerometer
const IPAddress outIp(255,255,255,255); // Client computer IP
const unsigned int outPort = 9999; // Client computer port
const unsigned int outPort2 = 7777; // Client computer port 2
const unsigned int localPort = 2390; // Local port to listen to OSC packets

// Variable
char ssid[] = "Romulo"; // EDIT: Network name
char pass[] = "romulo182"; // EDIT: Network password

WiFiUDP Udp; // Instance that allows sending and receiving packets using UDP packet
int GyX, GyY, GyZ; // Gyroscope X, Y and Z axis
int minVal=0; // Minimum value of MPU6050
int maxVal=65536;

/**
 * Reads from a qTouch-enabled pin and returns HIGH or LOW.
 * The threshold required for returning HIGH can be adjusted by changing the
 * TOUCH_THRESHOLD constant.
 *
 * @param pin The pin to read from
 * @returns HIGH if the value read from the pin is greater than TOUCH_THRESHOLD, LOW otherwise
*/
int capTouchRead(uint8_t pin) {
  // Return HIGH if the value read on the pin is greater than TOUCH_THRESHOLD
  if (touchRead(pin) >= TOUCH_THRESHOLD) {
    return HIGH;
  }

  // Otherwise, return LOW
  return LOW;
}

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
  Udp.beginPacket(ip, port);
  message.send(Udp);
  Udp.endPacket();

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
  Udp.begin(localPort);
  Serial.print("Local port: ");
  Serial.println(localPort);

  // Input touch pin
  pinMode(TOUCH_PIN, INPUT);

  // Setting MPU6050 accelerometer
  Wire.begin();
  Wire.beginTransmission(MPU); // Starting broadcast transmission with MPU address
  Wire.write(0X6B);

  // Reading the MPU6050 accelerometer
  Wire.write(0);
  Wire.endTransmission(true);
}

void loop() {
  // Touch sensor logic
  int value = capTouchRead(TOUCH_PIN); // Reading the touch sensor
  Serial.println(value); // Print touch sensor in serial monitor
  delay(50); // Touch sensor reading time (50 ms)

  // Accelerometer MPU6050 logic
  Wire.beginTransmission(MPU);
  Wire.write(0X3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 14, 1); // Reading MPU6050 data (14 bytes)

  // Reading the gyroscope
  GyX = Wire.read() << 8 | Wire.read();  //0x3B (GYRO_XOUT_H) & 0x3C (GYRO_XOUT_L)
  GyY = Wire.read() << 8 | Wire.read();  //0x3D (GYRO_YOUT_H) & 0x3E (GYRO_YOUT_L)
  GyZ = Wire.read() << 8 | Wire.read();  //0x3F (GYRO_ZOUT_H) & 0x40 (GYRO_ZOUT_L)

  // Change the gyroscope's range (0º to 180º)
  int xAng = map(GyX, minVal, maxVal, 0, 180);
  int yAng = map(GyY, minVal, maxVal, 0, 180);
  int zAng = map(GyZ, minVal, maxVal, 0, 180);

  // Send X axis to serial monitor
  Serial.print(" | GyX = "); Serial.print(xAng);
  // Send Y axis to serial monitor
  Serial.print(" | GyY = "); Serial.print(yAng);
  // Send Z axis to serial monitor
  Serial.print(" | GyZ = "); Serial.println(zAng);
  delay(300); // Gyroscope reading time (300 ms)

  // Send touch sensor message to the client with OSC protocol
  sendOSCMessage(outIp, outPort, "/value", value);
  delay(500);

  // Sending accelerometer X-axis message to Pure Data
  sendOSCMessage(outIp, outPort, "/gyx", xAng);
  delay(10);

  // Sending accelerometer X-axis message to Processing
  sendOSCMessage(outIp, outPort2, "/gyx", xAng);
  delay(10);

  // Sending accelerometer Y-axis message to Pure Data
  sendOSCMessage(outIp, outPort, "/gyy", yAng);
  delay(10);

  // Sending accelerometer Y-axis message to Processing
  sendOSCMessage(outIp, outPort2, "/gyy", yAng);
  delay(10);

  // Sending accelerometer Z axis message to Pure Data
  sendOSCMessage(outIp, outPort, "/gyz", zAng);
  delay(100);
}
