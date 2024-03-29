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
  /**
   * @brief Construct a new OSCEndpoint object that sends a UDP broadcast to
   * the given remote port using the given socket.
   *
   * @param socket Reference to an UDP socket
   * @param remotePort Remote port to send broadcast to
   */
  OSCEndpoint(WiFiUDP& socket, uint16_t remotePort) : OSCEndpoint(socket, IPAddress(255, 255, 255, 255), remotePort) {}

  /**
   * @brief Construct a new OSCEndpoint object that sends messages to the given
   * IP address and port using the given UDP socket.
   *
   * @param socket Reference to an UDP socket
   * @param remoteAddress  Remote address to send messages to
   * @param remotePort Remote port to send messages to
   */
  OSCEndpoint(WiFiUDP& socket, IPAddress remoteAddress, uint16_t remotePort) : socket(socket), remoteAddress(remoteAddress), remotePort(remotePort) {}

  /**
   * @brief Sends an OSC packet with the given route and value to the endpoint
   * provided in the constructor.
   *
   * @param route OSC route for the message
   * @param value Value to be contained in the OSC message
   */
  void sendMessage(const char route[], int32_t value);
};

#endif
