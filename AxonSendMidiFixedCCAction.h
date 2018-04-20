/* originally by Simon Peace
 * Send Midi Control Change Action Class
 * VERSION 1.0 19/02/2018
 */
#ifndef AXON_SENDMIDIFIXEDCCACTION_h
#define AXON_SENDMIDIFIXEDCCACTION_h

#include "AxonSendMidiCCAction.h"
#include "AxonEvent.h"
#include "Arduino.h"

class AxonSendMidiFixedCCAction: public AxonSendMidiCCAction					// Midi Control Change action class derived from AxonMidiChannelBasedAction
{
	public:
		AxonSendMidiFixedCCAction( uint8_t network, uint8_t channel, uint8_t cc, uint8_t value );

		void execute(  AxonAction *sender, AxonEvent *event );								// the execute method
	private:
		uint8_t _val = 0xFF;
};

#endif