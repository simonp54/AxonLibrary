#ifndef AXON_EVENTCLIENT_h
#define AXON_EVENTCLIENT_h

#include "AxonEventManager.h"
#include "AxonEvent.h"

class AxonEventManager;				// forward reference

class AxonEventClient
{
	public:
		virtual AxonEventClient() { }
		
		virtual void event( AxonEvent *event );
	protected:
	private:
};

#endif