#include "StateFromButton.h"

StateFromButton::StateFromButton(RecieverChannel *reciever, Operand operand, long period) {
	_reciever = reciever;
	_activatePeriod = period;
	_buttonPressed = false;
	_hasChanged = false;
	_buttonPressedAt = 0;
	_recieverMidValue = reciever->getMaxSignal() - (reciever->getMaxSignal() - reciever->getMinSignal()) / 4;
        _buttonPressedFor = 0;
        _pressStateAlradyReturned = false;
        _operand = operand;
}

void StateFromButton::read() {
	int value = _reciever->getValue();

        if (value == 0) {
          // error during recieve. ignore value
          return;
        }

    bool newButtonPressed = value > _recieverMidValue;
    if (newButtonPressed && newButtonPressed != _buttonPressed) {
        // button freshly pressed
        _buttonPressedAt = millis();
    } else {
        // check if already returned hasChanged
        if (!_pressStateAlradyReturned  && _buttonPressed) {
            if (_operand == GRATER_THAN) {
                // don't wait until released
                _buttonPressedFor = millis() - _buttonPressedAt;
                if (_buttonPressedFor >= _activatePeriod) {
                    _hasChanged = true;
                    _pressStateAlradyReturned = true;
                    
                }
            }
            if (_operand == LESS_THAN) {
                if (!newButtonPressed) {
                    // button released
                    _buttonPressedFor = millis() - _buttonPressedAt;
                    if (_buttonPressedFor < _activatePeriod) {
                        _hasChanged = true;
                    }
                }
            }
        }
    }
        

  if (_buttonPressed != newButtonPressed) {
      // state changed
      _pressStateAlradyReturned = false;
  }
  _buttonPressed = newButtonPressed;
}

bool StateFromButton::hasChanged() {
	if (_hasChanged) {
		_hasChanged = false;
		return true;
	} else {
		return false;
	}
}

bool StateFromButton::isOn() {
  return true;
}
