#ifndef __STATEFROMBUTTON_H__
#define __STATEFROMBUTTON_H__
#define RESULT_ALREADY_RETURNED 0

#include "RecieverChannel.h"
#include "State.h"

enum Operand {
  GRATER_THAN,
  LESS_THAN
};

class StateFromButton: public State {
	public:
		StateFromButton(RecieverChannel *reciever, Operand operand, long period);
		void read();
		bool hasChanged();
                bool isOn();
 	private:
		RecieverChannel *_reciever;
                Operand _operand;
		bool _buttonPressed;
		long _buttonPressedAt;
		long _activatePeriod;
		bool _hasChanged;
                int _recieverMidValue;
                long _buttonPressedFor;
                bool _pressStateAlradyReturned;
};

#endif
