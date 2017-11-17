#ifndef __DigitalChannel_h__
#define __DigitalChannel_h__

#include "Arduino.h"
#include "Channel.h"

class DigitalChannel : public Channel {
	public:
		DigitalChannel(int pin);
    void read();
    int getValue();
    int getMaxSignal();
    int getMinSignal();
    void dropNextValue();
	private:
		const int _minSignal = 1;
		const int _maxSignal = 100;
		int _value;
   int _pin;
};

#endif
