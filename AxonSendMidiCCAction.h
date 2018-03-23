/* originally by Simon Peace
 * Send Midi Control Change Action Class
 * VERSION 1.0 19/02/2018
 */
#ifndef AXON_SENDMIDICCACTION_h
#define AXON_SENDMIDICCACTION_h

#include "AxonMidiChannelBasedAction.h"
#include "AxonEvent.h"
#include "Arduino.h"

class AxonSendMidiCCAction: public AxonMidiChannelBasedAction					// Midi Control Change action class derived from AxonMidiChannelBasedAction
{
	public:
		void setCC( uint8_t cc );
		void setVal( uint8_t val );
		void fixVal( bool fix ) { _fixVal = fix; }
		void execute(  AxonAction *sender, AxonEvent *event );								// the execute method
	private:
		bool _fixVal = false;											// in general the value changes with "event input"
																		// but if this is true, ignore event input value
		uint8_t _cc = 0xFF;												// storage for the control change number
		uint8_t _val = 0xFF;											// the value to send to the controller
};

#endif