/* originally by Simon Peace
 * Midi Program Change Action Class
 * VERSION 1.0 19/02/2018
 */
#ifndef AXON_MIDICHANNELBASEDACTION_h
#define AXON_MIDICHANNELBASEDACTION_h

#include "AxonMidiBaseAction.h"
#include "Arduino.h"

class AxonMidiChannelBasedAction: public AxonMidiBaseAction							// Midi base Action class derived from AxonAction
{
	public:
		void setChannel( uint8_t channel );
		void execute( AxonAction *sender, AxonEvent *event);									// the execute method
	protected:
		uint8_t _channel = 0xFF;										// storage for the channel
};

#endif