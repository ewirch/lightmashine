#include "Counter.h"

Counter::Counter(State *stateSource, int maxCount) {
	_stateSource = stateSource;
	_count = 0;
	_hasChanged = false;
	_maxCount = maxCount;
}

void Counter::read() {
  _stateSource->read();
	if (_stateSource->hasChanged() && _stateSource->isOn()) {
		_hasChanged = true;
		_count++;
		if (_count >= _maxCount) {
			_count = 0;
		}
	}
}

bool Counter::hasChanged(){
	if (_hasChanged) {
		_hasChanged = false;
		return true;
	} else {
		return false;
	}
}

int Counter::getCount(){
	return _count;
}

void Counter::reset() {
  _count = 0;
}
