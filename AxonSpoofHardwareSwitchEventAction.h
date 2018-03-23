/* originally by Simon Peace
 * spoof HardwareSwitch Event Action
 * VERSION 1.0 20/03/2018
 */
#ifndef AXON_SPOOF_HARDWARE_SWITCH_EVENT_ACTION_h
#define AXON_SPOOF_HARDWARE_SWITCH_EVENT_ACTION_h

#include "AxonAction.h"
#include "Arduino.h"

class AxonSpoofHardwareSwitchEventAction: public AxonAction							// Midi base Action class derived from AxonAction
{
	public:
		void setSwitchNumber( uint8_t switchNumber ) { _switchNumber = switchNumber; }
		void setSwitchState( bool switchState ) { _switchState = switchState; }
	
		void execute( AxonAction *sender, AxonEvent *event);									// the execute method
	protected:
		uint8_t _switchNumber;
		bool _switchState;
};

#endif