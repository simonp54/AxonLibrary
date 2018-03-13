/*
 * AxonLatchingSwitch - an object that watches a switch "Subject"... and executes configured commands for "on" and "off"
 */
#ifndef AXON_LATCHINGSWITCH_h
#define AXON_LATCHINGSWITCH_h

#include "AxonEventClient.h"

class AxonLatchingSwitch : public AxonEventClient
{
	public:
		void event( AxonEvent *event );
	private:
		bool _switchState = false;
		bool _ignoreSubsequentDown = false;
};

#endif