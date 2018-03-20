/*
 * AxonOnOffDisplay - an object that watches a software switch events... and draws on or off on a specified screen
 */
#ifndef AXON_RADIOGROUP_h
#define AXON_RADIOGROUP_h

#include "AxonEventClient.h" 
#include "AxonHardwareSwitchEvent.h"

class AxonRadioSwitchGroupEventClient : public AxonEventClient
{
	public:
		AxonRadioSwitchGroupEventClient( uint8_t switchNumber );
		~AxonRadioSwitchGroupEventClient();
		void addSwitch( uint8_t switchNumber );
		void removeSwitch( uint8_t switchNumber );
	
		void event( AxonEvent *event );
	private:
		static const uint8_t _MAX_EVENTS = 24;
		uint8_t _myVirtualSwitchNumber;
		uint8_t _storedIndex;
		
		uint8_t _eventCount = 0;
		AxonHardwareSwitchEvent *_eventList[_MAX_EVENTS];
};

#endif