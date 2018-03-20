#include "AxonChannelMidiEvent.h"
#include "AxonEventTypeNumbers.h"
#include "Arduino.h"

#include "AxonDebugDefines.h"

AxonChannelMidiEvent::AxonChannelMidiEvent()
{
	_groupID = AXON_CHANNEL_MIDI_EVENT_TYPE;
}

bool AxonChannelMidiEvent::exactMatch(AxonEvent *event)
{
#ifdef DEBUG_CHANNEL_MIDI_EVENT
	Serial.println( F("AxonChannelMidiEvent::exactMatch") );
#endif
	if (AxonMidiEvent::exactMatch(event))
	{

		AxonChannelMidiEvent *tmp = event;
		if (tmp->getChannel() == _channel)
		{
#ifdef DEBUG_CHANNEL_MIDI_EVENT
			Serial.print( _groupID );
			Serial.print( F(":") );
			Serial.println( _channel );
			Serial.println( F(" channel matches (AKA EXACTMATCH)") );
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