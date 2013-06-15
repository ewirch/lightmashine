#ifndef __RECIEVER_H__
#define __RECIEVER_H__

#include "Arduino.h"
	
class RecieverChannel {
	public:
		RecieverChannel(int pin, int minSignal, int maxSignal);	
		void read();
		int getValue();
		int getMaxSignal();
		int getMinSignal();
	private:
		int _maxSignal;
		int _minSignal;
		int _pin;
		int _value;
		int pulseInSave();
};

#endif
