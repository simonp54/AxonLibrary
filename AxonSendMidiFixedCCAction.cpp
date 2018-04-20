/* originally by Simon Peace
 * Midi Control Change Action Class
 * VERSION 1.0 19/02/2018
 */
#include "AxonSendMidiFixedCCAction.h"
#include "AxonMidi.h"
#include "AxonSwitchEvent.h"
#include "Arduino.h"

#include "AxonDebugDefines.h"
#include "AxonCheckMem.h"

AxonSendMidiFixedCCAction::AxonSendMidiFixedCCAction( uint8_t network, uint8_t channel, uint8_t cc, uint8_t value ) : AxonSendMidiCCAction( network, channel, cc )
{	
	if ( (value >= 0) && (value <= 127) )
	{
		_val = value;
	}
	else
	{
		Serial.print( F("AxonSendMidiFixedCCAction::setvalue bad  value=") );
		Serial.println( value );
	}
}

void AxonSendMidiFixedCCAction::execute( AxonAction *sender, AxonEvent *event )		// use the midi implementation to send the control change
{
#ifdef DEBUG_SEND_MIDI_CC_ACTION
	Serial.println( F("AxonSendMidiFixedCCAction::execute") );
#endif
	
	
	if ( (_network != 0xFF) && (_channel != 0xFF) && (_cc != 0xFF) && (_val != 0xFF) )
	{
		AxonMidi::instance()->sendCC( _network, _channel, _cc, _val );
	}
	else
	{
		Serial.println( F("Axon CC Action tried to Execute without valid parameters") );
		Serial.print( _network );
		Serial.print( F(":") );
		Serial.print( _channel );
		Serial.print( F(":") );
		Serial.print( _cc );
		Serial.print( F(":") );
		Serial.println( _val );
	}
}