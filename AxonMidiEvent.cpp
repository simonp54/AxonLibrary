#include "AxonMidiEvent.h"
#include "AxonEventTypeNumbers.h"
#include "Arduino.h"

#include "AxonDebugDefines.h"

AxonMidiEvent::AxonMidiEvent()
{
	_groupID = AXON_MIDI_EVENT_TYPE;
}

bool AxonMidiEvent::exactMatch( AxonEvent *event )
{
#ifdef DEBUG_MIDI_EVENT
	Serial.println( F("AxonMidiEvent::exactMatch") );
	Serial.println( F("AxonMidiEvent::sameType") );
#endif
	if (AxonMidiEvent::sameType(event))
	{

		AxonMidiEvent *tmp = event;
		if (tmp->getNetwork() == _network)
		{
#ifdef DEBUG_MIDI_EVENT
			Serial.print( _groupID );
			Serial.print( F(":") );
			Serial.println( _network );
			Serial.println( F(" network matches (AKA EXACTMATCH)") );
#endif
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}