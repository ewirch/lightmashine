#include "RecieverChannel.h"

RecieverChannel::RecieverChannel(int pin, int minSignal, int maxSignal) {
	_pin = pin;
	_maxSignal = maxSignal;
	_minSignal = minSignal;
}

void RecieverChannel::read() {
	_value = pulseInSave();
}	

int RecieverChannel::getValue() {
	return _value;
}	

int RecieverChannel::pulseInSave() {
	int val = pulseIn(_pin, HIGH, 10000);
	if (val == 0) return 0;
	if (val < _minSignal) {
		val = _minSignal;
	}
	if (val > _maxSignal) {
		val = _maxSignal;
	}
	return val;
}

int RecieverChannel::getMaxSignal() {
	return _maxSignal;
}

int RecieverChannel::getMinSignal() {
	return _minSignal;
}
