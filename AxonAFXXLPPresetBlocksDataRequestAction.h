#ifndef AXON_AXEFXXLPLUSPRESETBLOCKSDATAREQUESTACTION_h
#define AXON_AXEFXXLPLUSPRESETBLOCKSDATAREQUESTACTION_h

#include "AxonMidiBaseAction.h"
#include "Arduino.h"

class AxonAFXXLPPresetBlocksDataRequestAction: public AxonMidiBaseAction	
{
	public:
		AxonAFXXLPPresetBlocksDataRequestAction( uint8_t network ) : AxonMidiBaseAction( network ) {};
		void execute( AxonAction *sender, AxonEvent *event);									// the execute method
	protected:
		static const uint8_t _payload[];
};

#endif