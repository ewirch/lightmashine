#ifndef __STATEFROMLEVER_H__
#define __STATEFROMLEVER_H__
#define RESULT_ALREADY_RETURNED 0

#include "RecieverChannel.h"
#include "State.h"


class StateFromLever: public State {
	public:
		StateFromLever(RecieverChannel *reciever, long activatePeriod);
		void read();
		bool hasChanged();
                bool isOn();
                virtual bool recieverValueToOnState(int value) = 0;
	private:
		RecieverChannel *_reciever;
		bool _isOn;
		long _changedSince;
		long _activatePeriod;
		bool _hasChanged;
};

#endif
