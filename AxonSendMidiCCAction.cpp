/* originally by Simon Peace
 * Midi Control Change Action Class
 * VERSION 1.0 19/02/2018
 */
#include "AxonSendMidiCCAction.h"
#include "AxonMidi.h"
#include "AxonSwitchEvent.h"
#include "Arduino.h"

#include "AxonDebugDefines.h"
#include "AxonCheckMem.h"

AxonSendMidiCCAction::AxonSendMidiCCAction( uint8_t network, uint8_t channel, uint8_t cc ) : AxonMidiChannelBasedAction( network, channel )
{	
	if ( (cc >= 0) && (cc <= 127) )
	{
		_cc = cc;
	}
	else
	{
		Serial.print( F("AxonSendMidiCCAction::setCC bad  cc=") );
		Serial.println( cc );
	}
}

void AxonSendMidiCCAction::execute( AxonAction *sender, AxonEvent *event )		// use the midi implementation to send the control change
{
	AxonSwitchEvent *tmp = new AxonSwitchEvent( 0 );		// number doesn't matter here
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
	if (event->sameType( tmp ))
	{
		AxonSwitchEvent *tmp2 = event;
		if ( (tmp2->getVal() >= 0) && (tmp2->getVal() <= 127) )
		{
			_val = tmp2->getVal();
		}
		else
		{
			Serial.print( F("AxonSendMidiCCAction::setVal bad  val=") );
			Serial.println( tmp2->getVal() );
		}
	}
	delete tmp;
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif

#ifdef DEBUG_SEND_MIDI_CC_ACTION
	Serial.println( F("AxonSendMidiCCAction::execute") );
	Serial.print( F("event switch value=") );
	Serial.println( _val );
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