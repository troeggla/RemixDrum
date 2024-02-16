#ifndef OSC_ENDPOINT_H
#define OSC_ENDPOINT_H

#include <Arduino.h>
#include <WiFiUdp.h>
#include <OSCMessage.h>

#define LOCAL_PORT 2390

class OSCEndpoint {
  WiFiUDP socket;
  IPAddress remoteAddress;
  uint8_t remotePort;
  uint8_t localPort;

public:
  OSCEndpoint(WiFiUDP socket, uint8_t remotePort) : OSCEndpoint(socket, IPAddress(255, 255, 255, 255), remotePort) {}
  OSCEndpoint(WiFiUDP socket, IPAddress remoteAddress, uint8_t remotePort) : OSCEndpoint(socket, remoteAddress, remotePort, LOCAL_PORT) {}
  OSCEndpoint(WiFiUDP socket, IPAddress remoteAddress, uint8_t remotePort, uint8_t localPort) : socket(socket), remoteAddress(remoteAddress), remotePort(remotePort), localPort(localPort) {}

  void sendMessage(const char route[], int32_t value);
};

#endif
