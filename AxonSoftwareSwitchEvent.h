#ifndef AXON_SOFTWARESWITCHEVENT_h
#define AXON_SOFTWARESWITCHEVENT_h

#include "Arduino.h"
#include "AxonSwitchEvent.h"

class AxonSoftwareSwitchEvent: public AxonSwitchEvent
{
	public:
		AxonSoftwareSwitchEvent( uint8_t switchNumber );
	private:
};

#endif