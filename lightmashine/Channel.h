#ifndef __Channel_h__
#define __Channel_h__

class Channel {
	public:
		virtual ~Channel() {};
		virtual void read() = 0;
		virtual int getValue() = 0;
		virtual int getMaxSignal() = 0;
		virtual int getMinSignal() = 0;
		virtual void dropNextValue() = 0;
};

#endif
