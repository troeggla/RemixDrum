#ifndef OSC_ENDPOINT_H
#define OSC_ENDPOINT_H

#include <Arduino.h>
#include <WiFiUdp.h>
#include <OSCMessage.h>

class OSCEndpoint {
  WiFiUDP& socket;
  IPAddress remoteAddress;
  uint16_t remotePort;

public:
  OSCEndpoint(WiFiUDP& socket, uint16_t remotePort) : OSCEndpoint(socket, IPAddress(255, 255, 255, 255), remotePort) {}
  OSCEndpoint(WiFiUDP& socket, IPAddress remoteAddress, uint8_t remotePort) : socket(socket), remoteAddress(remoteAddress), remotePort(remotePort) {}

  void sendMessage(const char route[], int32_t value);
};

#endif
