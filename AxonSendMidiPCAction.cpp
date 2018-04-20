/* originally by Simon Peace
 * Send Midi Program Change Action Class
 * VERSION 1.0 19/02/2018
 */
#include "AxonSendMidiPCAction.h"
#include "AxonMidi.h"
#include "Arduino.h"

AxonSendMidiPCAction::AxonSendMidiPCAction( uint8_t network, uint8_t channel, uint8_t pc ): AxonMidiChannelBasedAction( network, channel )
{	
	if ( (pc >= 0) && (pc <= 127) )
	{
		_pc = pc;
	}
}


void AxonSendMidiPCAction::execute( AxonAction *sender, AxonEvent *event)													// use the midi implementation to send the program change
{
	if ( (_network != 0xFF) && (_channel != 0xFF) && (_pc != 0xFF) )
	{
		AxonMidi::instance()->sendPC( _network, _channel, _pc );
	}
	else
	{
		Serial.println( F("Axon CC Action tried to Execute without valid parameters") );
	}
}