#ifndef CAPACITIVE_TOUCH_PAD_H
#define CAPACITIVE_TOUCH_PAD_H

#include <Arduino.h>

#define TOUCH_THRESHOLD 150000 // Threshold for recognising touch on capacitive touch pins

class CapacitiveTouchPad {
  uint8_t pin;
  touch_value_t threshold;

public:
  /**
   * @brief Construct a new Capacitive Touch Pad object for a touch pad on the
   * given pin with the default threshold value.
   *
   * @param pin Pin that the capacitive touch pad is attached to
   */
  CapacitiveTouchPad(uint8_t pin) : CapacitiveTouchPad(pin, TOUCH_THRESHOLD) {}

  /**
   * @brief Construct a new Capacitive Touch Pad object for a touch pad on the
   * given pin with the given threshold value.
   *
   * @param pin Pin that the capacitive touch pad is attached to
   * @param threshold Threshold for detecting HIGH state of the touch pad
   */
  CapacitiveTouchPad(uint8_t pin, touch_value_t threshold) : pin(pin), threshold(threshold) {
    // Input touch pin
    pinMode(pin, INPUT);
  }

  /**
   * @brief Determines whether the touch pad is being touched, i.e. if the
   * value read from the pin is above the threshold.
   *
   * @return uint8_t HIGH if the read value is above the threshold, LOW otherwise
   */
  uint8_t isTouched();

  /**
   * @brief Returns the value read from the capacitive touch pad.
   *
   * @return touch_value_t Value read from thye touch pad.
   */
  touch_value_t touchReadValue();
};

#endif
