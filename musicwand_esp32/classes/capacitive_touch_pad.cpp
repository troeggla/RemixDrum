#include "capacitive_touch_pad.hpp"

uint8_t CapacitiveTouchPad::isTouched() {
  // Return HIGH if the value read on the pin is greater than the threshold
  if (this->touchReadValue() >= this->threshold) {
    return HIGH;
  }

  return LOW;
}

touch_value_t CapacitiveTouchPad::touchReadValue() {
  return touchRead(this->pin);
}
