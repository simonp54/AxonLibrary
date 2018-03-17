#ifndef AXON_AXEFXXLPLUSSCENENUMBERREQUESTACTION_h
#define AXON_AXEFXXLPLUSSCENENUMBERREQUESTACTION_h

#include "AxonMidiBaseAction.h"
#include "Arduino.h"

class AxonAxeFXXLPlusSceneNumberRequestAction: public AxonMidiBaseAction	
{
	public:
		void execute(AxonEvent *event);									// the execute method
	protected:
		static const uint8_t _payload[];
};

#endif