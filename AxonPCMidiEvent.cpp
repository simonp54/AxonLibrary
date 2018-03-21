#include "AxonPCMidiEvent.h"
#include "AxonEventTypeNumbers.h"
#include "Arduino.h"

#include "AxonDebugDefines.h"

AxonPCMidiEvent::AxonPCMidiEvent()
{
	_groupID = AXON_PC_MIDI_EVENT_TYPE;
}

bool AxonPCMidiEvent::exactMatch(AxonEvent *event)
{
#ifdef DEBUG_PC_MIDI_EVENT_VERBOSE
	Serial.println( F("AxonPCMidiEvent::exactMatch" ) );
#endif
	if (AxonPCMidiEvent::sameType(event))
	{
		if (AxonChannelMidiEvent::exactMatch(event))
		{
			AxonPCMidiEvent *tmp = event;

			if (tmp->getPC() == _pc)
			{
#ifdef DEBUG_PC_MIDI_EVENT
				Serial.print( _groupID );
				Serial.print( F(":") );
				Serial.println( _pc );
				Serial.println( F(" PC matches (AKA EXACTMATCH)") );
#endif
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	else
	{
		return false;
	}
}