#ifndef FLAGSTATE_H_
#define FLAGSTATE_H_

#include "State.h"

class FlagState {
	public:
		FlagState(State *stateSource, bool startState);
		void read();
		bool hasChanged();
		bool isOn();
	private:
		State *_stateSource;
		bool _on;
		bool _hasChanged;
};



#endif /* FLAGSTATE_H_ */
