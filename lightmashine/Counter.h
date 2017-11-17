
#ifndef COUNTER_H_
#define COUNTER_H_

#include "State.h"

class Counter {
	public:
		Counter(State *stateSource, int maxCounter);
		void read();
		bool hasChanged();
		int getCount();
                void reset();
	private:
		State *_stateSource;
		int _count;
		int _maxCount;
		bool _hasChanged;
};



#endif /* COUNTER_H_ */
