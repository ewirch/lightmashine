#ifndef __State_h__
#define __State_h__

class State {
	public:
		virtual ~State() {};
		virtual void read() = 0;
		virtual bool hasChanged() = 0;
		virtual bool isOn() = 0;
};

#endif
