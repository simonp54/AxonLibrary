#ifndef AXON_AXEFXXLPLUSPRESETNAMEREQUESTACTION_h
#define AXON_AXEFXXLPLUSPRESETNAMEREQUESTACTION_h

#include "AxonMidiBaseAction.h"
#include "Arduino.h"

class AxonAFXXLPPresetNameRequestAction: public AxonMidiBaseAction	
{
	public:
		void execute( AxonAction *sender, AxonEvent *event);									// the execute method
	protected:
		static const uint8_t _payload[];
};

#endif