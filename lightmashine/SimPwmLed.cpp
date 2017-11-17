#include "SimPwmLed.h"

SimPwmLed::SimPwmLed(byte pin) {
   _pin = pin;
   pinMode(pin, OUTPUT);
   
   _updatesPerTargetLightnessPoint = 0;
    
   _fromTargetLightness = NOT_SET;
   _toTargetLightness = NOT_SET;
    
   _counter = 0;
   _updatesBetweenFrames = 0;
   _updatesPerTargetLightnessPoint = 0;
   _updatesUntilNextTargetLightPoint = 0;
   _targetLightness = 0;
   _increasing = true;
   _state = LOW;
}

void SimPwmLed::set(byte percent) {
  bool immediate = false;
  
  if (percent == _) {
    immediate = true;
    percent = 0;
  }
  if (percent == X) {
    immediate = true;
    percent = 100;
  }
  if (percent > 100) percent = 100;

  if (immediate) {
    _fromTargetLightness = percent;
    _toTargetLightness = percent;
    _updatesPerTargetLightnessPoint = _updatesBetweenFrames;
  } else {
    _fromTargetLightness = _toTargetLightness;
    _toTargetLightness = percent;
  
    if (_updatesBetweenFrames > 0) {
      int diff;
      if (_toTargetLightness > _fromTargetLightness) {
        diff = _toTargetLightness - _fromTargetLightness;
        _increasing = true;
      } else {
        diff = _fromTargetLightness - _toTargetLightness;
        _increasing = false;
      }
      if (diff == 0) {diff = 1;} // avoid division by zero
      _updatesPerTargetLightnessPoint = _updatesBetweenFrames / diff;
    }
  }

  if (_fromTargetLightness == NOT_SET) {
    // very first run
    _targetLightness = percent;
  } else {
    _targetLightness = _fromTargetLightness;
  }
  _updatesBetweenFrames = 0;
}

void SimPwmLed::update() {
  if (_counter < _targetLightness) {
    fastWrite(HIGH);
  } else {
    fastWrite(LOW);
  }
  _counter++;
  if (_counter == 100) _counter = 0;

  _updatesUntilNextTargetLightPoint--;
  if (_updatesUntilNextTargetLightPoint <= 0) {
    _updatesUntilNextTargetLightPoint = _updatesPerTargetLightnessPoint;

    if (_increasing) {
      _targetLightness++;
      if (_targetLightness > _toTargetLightness) _targetLightness = _toTargetLightness;
    } else {
      _targetLightness--;
      if (_targetLightness < _toTargetLightness) _targetLightness = _toTargetLightness;
    }
  }

  _updatesBetweenFrames++;
}

void SimPwmLed::fastWrite(byte newState) {
  if (_state != newState) {
      digitalWrite(_pin, newState);
     _state = newState;
  }
}
