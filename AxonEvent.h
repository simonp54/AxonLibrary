#ifndef AXON_EVENT_h
#define AXON_EVENT_h

#include "Arduino.h"


class AxonEvent
{
	public:
		AxonEvent();
		virtual ~AxonEvent() {};
		
		uint16_t getGroupID() { return _groupID; }
		
		bool sameType( AxonEvent *event );
		virtual bool exactMatch( AxonEvent *event );
	protected:
		uint16_t _groupID;
	private:
};

#endif
