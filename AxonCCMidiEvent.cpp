#include "AxonCCMidiEvent.h"
#include "AxonEventTypeNumbers.h"
#include "Arduino.h"

#include "AxonDebugDefines.h"

AxonCCMidiEvent::AxonCCMidiEvent()
{
	_groupID = AXON_CC_MIDI_EVENT_TYPE;
}

bool AxonCCMidiEvent::exactMatch(AxonEvent *event)
{
#ifdef DEBUG_AXON_CC_MIDI_EVENT
	Serial.println( F("AxonCCMidiEvent::exactMatch" ) );
#endif
	if (AxonChannelMidiEvent::exactMatch(event))
	{

		AxonCCMidiEvent *tmp = event;
		if (tmp->getCC() == _cc)
		{
#ifdef DEBUG_AXON_CC_MIDI_EVENT
			Serial.print( _groupID );
			Serial.print( F(":") );
			Serial.println( _cc );
			Serial.println( F(" cc matches (AKA EXACTMATCH)") );
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