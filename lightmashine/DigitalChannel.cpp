#include "DigitalChannel.h"

DigitalChannel::DigitalChannel(int pin) {
  _pin = pin;
  _value = 0;

  pinMode(pin, INPUT_PULLUP);
}

void DigitalChannel::read() {
  // We're reading pin value inverse. Since we use INPUT_PULLUP, a HIGH value means no button is pressed.
  if (digitalRead(_pin) == LOW) {
  	_value = _maxSignal;
  } else {
  	_value = _minSignal;
  }
}

int DigitalChannel::getValue() {
  return _value;
}

int DigitalChannel::getMaxSignal() {
  return _maxSignal;
}

int DigitalChannel::getMinSignal() {
  return _minSignal;
}

void DigitalChannel::dropNextValue() {
}
