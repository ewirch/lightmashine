#include "StateFromLeverUp.h"

StateFromLeverUp::StateFromLeverUp(Channel *reciever, long activatePeriod)
:StateFromLever(reciever, activatePeriod)
 {
	 int minSignal = reciever->getMinSignal();
	 int maxSignal = reciever->getMaxSignal();
	_upperEnableBorder = ((maxSignal - minSignal) * 0.6 + minSignal);
}

bool StateFromLeverUp::recieverValueToOnState(int value) {
	return value > _upperEnableBorder;
}
