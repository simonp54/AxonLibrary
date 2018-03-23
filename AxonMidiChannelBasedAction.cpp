/* originally by Simon Peace
 * Midi Program Change Action Class
 * VERSION 1.0 19/02/2018
 */
#include "AxonMidiChannelBasedAction.h"
#include "Arduino.h"

void AxonMidiChannelBasedAction::setChannel( uint8_t channel )
{
	if ( (channel > 0) && (channel <= 16) )
	{
		_channel = channel;
	}
}

void AxonMidiChannelBasedAction::execute( AxonAction *sender, AxonEvent *event)													// use the midi implementation to send the program change
{
	Serial.println( F("AxonMidiChannelBasedAction tried to Execute... (nonsense)") );
}