#include "AxonSysExMidiEvent.h"
#include "AxonEventTypeNumbers.h"
#include "Arduino.h"

#include "AxonDebugDefines.h"

AxonSysExMidiEvent::AxonSysExMidiEvent()
{
	_groupID = AXON_SYSEX_MIDI_EVENT_TYPE;
}

AxonSysExMidiEvent::~AxonSysExMidiEvent()
{
	deleteData();
}

void AxonSysExMidiEvent::deleteData()
{
#ifdef DEBUG_SYSEX_MIDI_EVENT
	Serial.println( F("AxonSysExMidiEvent::deleteData") );
#endif
	if (_size > 0)
	{
#ifdef DEBUG_SYSEX_MIDI_EVENT
		Serial.print( F("buffer existed deleting memory ") );
		Serial.print( _size );
		Serial.println( F(" bytes") );
#endif
		free(_array);
		_size = 0;
#ifdef DEBUG_SYSEX_MIDI_EVENT
		Serial.println( F("...deleted") );
#endif
	}
}

uint8_t AxonSysExMidiEvent::getByte( uint8_t pos )
{
	if (pos <= _size)
	{
		return _array[pos];
	}
	else
	{
		return 0xFF;
	}
}

void AxonSysExMidiEvent::copyData( uint8_t* array, uint8_t size )
{
#ifdef DEBUG_SYSEX_MIDI_EVENT
	Serial.println( F("AxonSysExMidiEvent::copyData") );
#endif

	deleteData();
	
	if (size > 0)
	{
#ifdef DEBUG_SYSEX_MIDI_EVENT
		Serial.print( F("allocating memory ") );
		Serial.println( size );
#endif
		_array = (uint8_t*) malloc (size);
		if (_array==NULL)
		{
#ifdef DEBUG_WARNINGS
			Serial.println( F("AxonSysExMidiEvent::Failed to allocate memory") );
#endif
			_size = 0;
		}
		else
		{
#ifdef DEBUG_SYSEX_MIDI_EVENT
			Serial.println( F("...allocated") );
#endif
			memcpy( _array, array, size );
#ifdef DEBUG_SYSEX_MIDI_EVENT
			Serial.print( F("copied ") );
			Serial.print( size );
			Serial.println( F(" bytes" ) );
#endif
			_size = size;
		}
	}
}

bool AxonSysExMidiEvent::exactMatch(AxonEvent *event)
{
#ifdef DEBUG_SYSEX_MIDI_EVENT
	Serial.println( F("AxonSysExMidiEvent::exactMatch") );
#endif
	if (AxonMidiEvent::exactMatch(event))
	{
		return true;
	}
}