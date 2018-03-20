/* originally by Simon Peace
 * Base Midi object wrapping Class
 * VERSION 1.0 19/02/2018
 */
#include "AxonMidi.h"
#include "AxonMidiImpl1.h"
#include "AxonMidiImpl2.h"
#include "Arduino.h"

#include "AxonDebugDefines.h"
#include "AxonCheckMem.h"


AxonMidi *AxonMidi::_instance = 0;

/*
 * Accessor method
 */
AxonMidi *AxonMidi::instance()
{
	if (!_instance)
	{
		_instance = new AxonMidi();
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
	}
	return _instance;
}

AxonMidi::AxonMidi()
{
	_midiNet[0] = new AxonMidiImpl1( );
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
	_midiNet[1] = new AxonMidiImpl2( );
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
}

void AxonMidi::sendCC(uint8_t network, uint8_t channel, uint8_t cc, uint8_t val )
{
#ifdef DEBUG_MIDI
	Serial.print( F("AxonMidi sending CC: Network=") );
	Serial.print( network );
	Serial.print( F(" Channel=") );
	Serial.print( channel );
	Serial.print( F(" CC=") );
	Serial.print( cc );
	Serial.print( F(" val=") );
	Serial.println( val );
#endif
	if ((network == 0) || (network == 1))
	{
		_midiNet[network]->sendCC( channel, cc, val );
	}
}

void AxonMidi::sendPC(uint8_t network, uint8_t channel, uint8_t pc)
{
#ifdef DEBUG_MIDI
	Serial.print( F("AxonMidi sending PC: Network=") );
	Serial.print( network );
	Serial.print( F(" Channel=") );
	Serial.print( channel );
	Serial.print( F(" PC=") );
	Serial.println( pc );
#endif
	if ((network == 0) || (network == 1))
	{
		_midiNet[network]->sendPC( channel, pc );
	}
}

void AxonMidi::sendSysEx( uint8_t network, uint8_t inLength, const uint8_t* inArray, bool inArrayContainsBoundaries )
{
#ifdef DEBUG_MIDI
	Serial.print( F("AxonMidi sending SysEx: Network=") );
	Serial.println( network );
#endif
	if ((network == 0) || (network == 1))
	{
		_midiNet[network]->sendSysEx( inLength, inArray, inArrayContainsBoundaries );
	}
}

void AxonMidi::read()
{
	_midiNet[0]->read();
	_midiNet[1]->read();
}