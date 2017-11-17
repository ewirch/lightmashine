#ifndef __STATEFROLEVERUP_H__
#define __STATEFROLEVERUP_H__

#include "Arduino.h"
#include "StateFromLever.h"


class StateFromLeverUp: public StateFromLever {
	public:
		StateFromLeverUp(RecieverChannel *reciever, long activatePeriod);
		bool recieverValueToOnState(int value);
	private:
		int _upperEnableBorder;
};

#endif
