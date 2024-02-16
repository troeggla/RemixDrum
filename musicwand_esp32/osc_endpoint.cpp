#include "osc_endpoint.hpp"

void OSCEndpoint::begin() {
  this->socket.begin(this->localPort);
}

void OSCEndpoint::sendMessage(const char route[], int32_t value) {
  // Init message and add value
  OSCMessage message(route);
  message.add(value);

  // Send message via UDP
  this->socket.beginPacket(this->remoteAddress, this->remotePort);
  message.send(socket);
  socket.endPacket();

  // Clear message
  message.empty();
}
