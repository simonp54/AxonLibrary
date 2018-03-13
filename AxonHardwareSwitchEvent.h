#ifndef AXON_HARDWARESWITCHEVENT_h
#define AXON_HARDWARESWITCHEVENT_h

#include "Arduino.h"
#include "AxonSwitchEvent.h"

class AxonHardwareSwitchEvent: public AxonSwitchEvent
{
	public:
		AxonHardwareSwitchEvent( uint8_t switchNumber );
	private:
};

#endif