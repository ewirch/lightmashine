#ifndef __STATEFROLEVERUP_H__
#define __STATEFROLEVERUP_H__

#include "StateFromLever.h"


class StateFromLeverUp: public StateFromLever {
	public:
		StateFromLeverUp(RecieverChannel *reciever, long activatePeriod);
		bool recieverValueToOnState(int value);
	private:
		int _upperEnableBorder;
};

#endif
