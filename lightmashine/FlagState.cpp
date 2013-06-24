#include "FlagState.h"

FlagState::FlagState(State *stateSource, bool startState) {
  _stateSource = stateSource;
  _on = startState;
  _hasChanged = false;
}

void FlagState::read() {
  _stateSource->read();
	if (_stateSource->hasChanged() && _stateSource->isOn()) {
		_hasChanged = true;
		_on = !_on;
	}
}
		
bool FlagState::hasChanged(){
	if (_hasChanged) {
		_hasChanged = false;
		return true;
	} else {
		return false;
	}
}

bool FlagState::isOn(){
	return _on;
}
