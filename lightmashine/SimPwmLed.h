#ifndef __SIM_PWN_LED__
#define __SIM_PWN_LED__

#include "Arduino.h"
#include "Led.h"
#include "constants.h"

#define NOT_SET 255

class SimPwmLed: public Led {
  public:
    SimPwmLed(byte pin);
    void set(byte percent);
    void update();
  private:
    void fastWrite(byte newState);
    
    byte _pin;
    int _updatesBetweenFrames;
    int _updatesPerTargetLightnessPoint;
    int _updatesUntilNextTargetLightPoint;
    bool _increasing;

    byte _fromTargetLightness;
    byte _toTargetLightness;

    int _targetLightness;
    byte _counter;
    byte _state;
};

#endif
