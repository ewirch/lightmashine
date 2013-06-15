#include "StateFromLeverDown.h"

StateFromLeverDown::StateFromLeverDown(RecieverChannel *reciever, long activatePeriod)
:StateFromLever(reciever, activatePeriod)
{
	int minSignal = reciever->getMinSignal();
	int maxSignal = reciever->getMaxSignal();
	_lowerEnableBorder = ((maxSignal - minSignal) * 0.4 + minSignal);
}

bool StateFromLeverDown::recieverValueToOnState(int value) {
	return value < _lowerEnableBorder;
}
