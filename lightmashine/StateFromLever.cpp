#include "StateFromLever.h"

StateFromLever::StateFromLever(RecieverChannel *reciever, long activatePeriod) {
	_reciever = reciever;
	_activatePeriod = activatePeriod;
	_isOn = false;
	_hasChanged = false;
	_changedSince = RESULT_ALREADY_RETURNED;
}

void StateFromLever::read() {
	int value = _reciever->getValue();

        if (value == 0) {
          // error during recieve. ignore value
          return;
        }
        
        boolean newIsOn = recieverValueToOnState(value);
	if (newIsOn != _isOn) {
                // button released
		_changedSince = millis();
		_isOn = newIsOn;
	} else {
		if (_changedSince != RESULT_ALREADY_RETURNED) {
			long now = millis();
			if ((now - _changedSince) > _activatePeriod) {
				_hasChanged = true;
				_changedSince = RESULT_ALREADY_RETURNED;
			}
		}
	}
}

bool StateFromLever::hasChanged() {
	if (_hasChanged) {
		_hasChanged = false;
		return true;
	} else {
		return false;
	}
}

bool StateFromLever::isOn() {
  return _isOn;
}
