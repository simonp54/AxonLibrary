/* originally by Simon Peace
 * Base action class for Midi (all of which need to know which AXON network port to use)
 * VERSION 1.0 19/02/2018
 */
#ifndef AXON_MIDIBASEACTION_h
#define AXON_MIDIBASEACTION_h

#include "AxonAction.h"
#include "Arduino.h"

class AxonMidiBaseAction: public AxonAction							// Midi base Action class derived from AxonAction
{
	public:
		void setNetwork( uint8_t network );
		void execute( AxonAction *sender, AxonEvent *event);									// the execute method
	protected:
		uint8_t _network = 0xFF;										// storage for network
};

#endif