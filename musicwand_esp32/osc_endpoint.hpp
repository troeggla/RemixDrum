#ifndef OSC_ENDPOINT_H
#define OSC_ENDPOINT_H

#include <Arduino.h>
#include <WiFiUdp.h>
#include <OSCMessage.h>

#define LOCAL_PORT 2390

class OSCEndpoint {
  IPAddress remoteAddress;
  uint8_t remotePort;
  uint8_t localPort;

  WiFiUDP socket;

public:
  OSCEndpoint(uint8_t remotePort) : OSCEndpoint(IPAddress(255, 255, 255, 255), remotePort) {}
  OSCEndpoint(IPAddress remoteAddress, uint8_t remotePort) : OSCEndpoint(remoteAddress, remotePort, LOCAL_PORT) {}
  OSCEndpoint(IPAddress remoteAddress, uint8_t remotePort, uint8_t localPort) : remoteAddress(remoteAddress), remotePort(remotePort), localPort(localPort) {}

  void begin();
  void sendMessage(const char route[], int32_t value);
};

#endif
