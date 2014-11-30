#include "RecieverChannel.h"

RecieverChannel::RecieverChannel(int pin, int minSignal, int maxSignal) {
  _maxSignal = maxSignal;
  _minSignal = minSignal;
  _pin = pin;
  _value = 0;
  _lastState = LOW;
  pinMode(pin, INPUT);

  _stateChanged = micros();
}

void RecieverChannel::read() {
  int newState = digitalRead(_pin);
  if (newState != _lastState) {
    if (_lastState == LOW) {
      // change from low to high, start measuring time
      _stateChanged = micros();
    }
    if (_lastState == HIGH) {
      // change from high to low, calculate passed time
      long now = micros();
      long time = now - _stateChanged;
      if (time > MIN_VALUE) {
        _value = trimValueToBoundaries(time);
      }
      _stateChanged = now;
    }
    _lastState = newState;
  }
}	

int RecieverChannel::getValue() {
  return _value;
}	

int RecieverChannel::trimValueToBoundaries(long val) {
  if (val < _minSignal) {
    return _minSignal;
  }
  if (val > _maxSignal) {
   return _maxSignal;
  }
  return val;
}

int RecieverChannel::getMaxSignal() {
  return _maxSignal;
}

int RecieverChannel::getMinSignal() {
  return _minSignal;
}
