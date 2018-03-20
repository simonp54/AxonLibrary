#ifndef AXON_AXEFXXLPLUSPRESETBLOCKSDATAREQUESTACTION_h
#define AXON_AXEFXXLPLUSPRESETBLOCKSDATAREQUESTACTION_h

#include "AxonMidiBaseAction.h"
#include "Arduino.h"

class AxonAFXXLPPresetBlocksDataRequestAction: public AxonMidiBaseAction	
{
	public:
		void execute(AxonEvent *event);									// the execute method
	protected:
		static const uint8_t _payload[];
};

#endif