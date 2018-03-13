#ifndef AXON_MIDIEVENT_h
#define AXON_MIDIEVENT_h

#include "Arduino.h"
#include "AxonEvent.h"

class AxonMidiEvent: public AxonEvent
{
	public:
		AxonMidiEvent();

		uint8_t getNetwork() { return _network; }
		void setNetwork(uint8_t network) { _network = network; }
		
		virtual bool exactMatch( AxonEvent *event );
	protected:
		uint8_t _network = 0;
};

#endif