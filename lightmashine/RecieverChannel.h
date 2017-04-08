#ifndef __RECIEVER_H__
#define __RECIEVER_H__

#include "Arduino.h"

#define MIN_VALUE 500

class RecieverChannel {
  public:
    RecieverChannel(int pin, int minSignal, int maxSignal);	
    void read();
    int getValue();
    int getMaxSignal();
    int getMinSignal();
    void dropNextValue();
  private:
    int _maxSignal;
    int _minSignal;
    int _pin;
    int _value;
    long _stateChanged;
    int _lastState;
    bool _dropNextValue;
    int trimValueToBoundaries(long val);
};

#endif
