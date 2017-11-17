#ifndef __PWM_LED_H__
#define __PWM_LED_H__

#include "Arduino.h"
#include "Led.h"
#include "constants.h"

class PwmLed: public Led {
  public:
    PwmLed(byte pin);
    void set(byte percent);
    void update();
  private:
    byte _pin;
    byte _oldPercent;
};

#endif
