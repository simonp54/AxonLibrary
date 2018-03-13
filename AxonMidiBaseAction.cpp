/* originally by Simon Peace
 * Base action class for Midi (all of which need to know which AXON network port to use)
 * VERSION 1.0 19/02/2018
 */
#include "AxonMidiBaseAction.h"
#include "Arduino.h"

void AxonMidiBaseAction::setNetwork( uint8_t network )
{
	if ( (network >= 0) && (network <= 1) )
	{
		_network = network;
	}
}


void AxonMidiBaseAction::execute(AxonEvent *event)													// use the midi implementation to send the program change
{
	Serial.println( F("AxonMidiBaseAction tried to Execute... (nonsense)") );
}