#ifndef __STATEFROMLEVER_DOWN__
#define __STATEFROMLEVER_DOWN__

#include "Arduino.h"
#include "Channel.h"
#include "StateFromLever.h"

class StateFromLeverDown: public StateFromLever {
	public:
		StateFromLeverDown(Channel *reciever, long activatePeriod);
		bool recieverValueToOnState(int value);
	private:
		int _lowerEnableBorder;
};



#endif
