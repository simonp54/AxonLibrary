#ifndef AXON_EVENTCLIENT_h
#define AXON_EVENTCLIENT_h

#include "AxonEventManager.h"
#include "AxonAction.h"
#include "AxonEvent.h"

class AxonEventManager;				// forward reference

class AxonEventClient
{
	public:
		void setOnAction( AxonAction *action );
		void setOffAction( AxonAction *action );
		void setOnChangeAction( AxonAction *action );
	
//		virtual AxonEventClient() { }
		
		virtual void event( AxonEvent *event );
	protected:
		AxonAction *_onAction = 0;
		AxonAction *_offAction = 0;
		AxonAction *_onChangeAction = 0;
	private:
};

#endif