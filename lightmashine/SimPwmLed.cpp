#include "SimPwmLed.h"

SimPwmLed::SimPwmLed(byte pin) {
   _pin = pin;
   pinMode(pin, OUTPUT);
   _counter = 0;
   _targetLightness = 0;
   set(0);
   update();
}

void SimPwmLed::set(byte percent) {
  if (percent > 100) percent = 100;

  _targetLightness = percent;
}

void SimPwmLed::update() {
  if (_counter < _targetLightness) {
    fastWrite(HIGH);
  } else {
    fastWrite(LOW);
  }
  _counter++;
  if (_counter == 100) _counter = 0;
}

void SimPwmLed::fastWrite(byte newState) {
  if (_state != newState) {
    digitalWrite(_pin, newState);
    _state = newState;
  }
}
