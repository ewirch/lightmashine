#ifndef __STATEFROMLEVER_DOWN__
#define __STATEFROMLEVER_DOWN__

#include "Arduino.h"
#include "RecieverChannel.h"
#include "StateFromLever.h"

class StateFromLeverDown: public StateFromLever {
	public:
		StateFromLeverDown(RecieverChannel *reciever, long activatePeriod);
		bool recieverValueToOnState(int value);
	private:
		int _lowerEnableBorder;
};



#endif
