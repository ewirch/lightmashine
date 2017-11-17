#ifndef __NOOP_LED_H__
#define __NOOP_LED_H__

#include "Arduino.h"
#include "Led.h"

class NoopLed: public Led {
  public:
    NoopLed(byte pin);
    void set(byte percent);
    void update();
};

#endif
