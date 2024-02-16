#ifndef CAPACITIVE_TOUCH_PAD_H
#define CAPACITIVE_TOUCH_PAD_H

#include <Arduino.h>

#define TOUCH_THRESHOLD 150000 // Threshold for recognising touch on capacitive touch pins

class CapacitiveTouchPad {
  uint8_t pin;
  touch_value_t threshold;

public:
  CapacitiveTouchPad(uint8_t pin) : CapacitiveTouchPad(pin, TOUCH_THRESHOLD) {}
  CapacitiveTouchPad(uint8_t pin, touch_value_t threshold) : pin(pin), threshold(threshold) {}

  uint8_t isTouched();
  touch_value_t touchReadValue();
};

#endif
