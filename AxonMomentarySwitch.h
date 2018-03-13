/*
 * AxonMomentarySwitch - an object that watches a switch "Subject"... and executes configured commands for "on" and "off"
 */
#ifndef AXON_MOMENTARYSWITCH_h
#define AXON_MOMENTARYSWITCH_h

#include "AxonEventClient.h" 

class AxonMomentarySwitch : public AxonEventClient
{
	public:
		void setInterval( uint16_t interval );
		uint16_t getInterval();
		void event( AxonEvent *event );
	private:
		bool _switchState = false;
		uint64_t _startMillis = 0;
		uint16_t _interval = 0;
};

#endif