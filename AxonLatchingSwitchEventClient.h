/*
 * AxonLatchingSwitchEventClient - an object that watches a switch "Subject"... and executes configured commands for "on" and "off"
 */
#ifndef AXON_LATCHINGSWITCH_h
#define AXON_LATCHINGSWITCH_h

#include "AxonEventClient.h"
#include "AxonHardwareSwitchEvent.h"

class AxonLatchingSwitchEventClient : public AxonEventClient
{
	public:
		AxonLatchingSwitchEventClient( uint8_t hardwareSwitchNumber );
		~AxonLatchingSwitchEventClient();

		void event( AxonEvent *event );
	private:
		bool _switchState = false;
		bool _ignoreSubsequentDown = false;
		
		AxonHardwareSwitchEvent *_hardwareSwitchEvent;
};

#endif