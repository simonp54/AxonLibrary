/*
 * AxonActionEventClient - an object that watches for switch events... and executes configured commands for "on", "off", "changed" etc...
 */
#ifndef AXON_ACTIONCLIENT_h
#define AXON_ACTIONCLIENT_h

#include "AxonEventClient.h"
#include "AxonEvent.h" 
#include "AxonAction.h"

class AxonActionEventClient : public AxonEventClient
{
	public:
		void setOnAction( AxonAction *action );
		void setOffAction( AxonAction *action );
		void setOnChangeAction( AxonAction *action );

		void event( AxonAction *sender, AxonEvent *event );
	private:
		AxonAction *_onAction = 0;
		AxonAction *_offAction = 0;
		AxonAction *_onChangeAction = 0;
};

#endif