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
		AxonSendMidiCCAction( uint8_t network, uint8_t channel, uint8_t cc );

		void execute(  AxonAction *sender, AxonEvent *event );								// the execute method
	protected:
		uint8_t _cc = 0xFF;					// storage for the control change number
		uint8_t _val = 0xFF;				// storage for the last used value
};

#endif