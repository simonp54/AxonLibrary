#ifndef AXON_AXEFXXLPLUSPRESETNAMEREQUESTACTION_h
#define AXON_AXEFXXLPLUSPRESETNAMEREQUESTACTION_h

#include "AxonMidiBaseAction.h"
#include "Arduino.h"

class AxonAxeFXXLPlusPresetNameRequestAction: public AxonMidiBaseAction	
{
	public:
		void execute(AxonEvent *event);									// the execute method
	protected:
		static const uint8_t _payload[];
};

#endif