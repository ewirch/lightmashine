#include "PwmLed.h"

PwmLed::PwmLed(byte pin) {
   _pin = pin;
   pinMode(pin, OUTPUT);
   _oldPercent = 255; // set wrong value, so set() will do work
   set(0);
}

void PwmLed::set(byte percent) {
  if (percent < 0) percent = 0;
  if (percent > 100) percent = 100;
  if (percent == 1) percent = 100;
  
  if (percent != _oldPercent) {
    analogWrite(_pin, map(percent, 0, 100, 0, 255));
    _oldPercent = percent;
  }
}

void PwmLed::update() {
}
