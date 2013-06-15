#ifndef __SIM_PWN_LED__
#define __SIM_PWN_LED__

#include "Arduino.h"
#include "Led.h"

class SimPwmLed: public Led {
  public:
    SimPwmLed(byte pin);
    void set(byte percent);
    void update();
  private:
    void fastWrite(byte newState);
    
    byte _pin;
    byte _targetLightness;
    byte _counter;
    byte _state;
};

#endif
