#include "AxonSongSelectMidiEvent.h"
#include "AxonEventTypeNumbers.h"
#include "Arduino.h"

#include "AxonDebugDefines.h"

AxonSongSelectMidiEvent::AxonSongSelectMidiEvent()
{
	_groupID = AXON_SONG_SELECT_MIDI_EVENT_TYPE;
}

bool AxonSongSelectMidiEvent::exactMatch(AxonEvent *event)
{
#ifdef DEBUG_SONG_SELECT_MIDI_EVENT_VERBOSE
	Serial.println( F("AxonSongSelectMidiEvent::exactMatch") );
#endif
	if (AxonSongSelectMidiEvent::sameType(event))
	{
		AxonSongSelectMidiEvent *tmp = event;

		if (tmp->getSongNumber() == _songNumber)
		{
#ifdef DEBUG_SONG_SELECT_MIDI_EVENT
			Serial.print( _groupID );
			Serial.print( F(":") );
			Serial.println( _songNumber );
			Serial.println( F(" songNumber matches (AKA EXACTMATCH)") );
#endif
			return true;
		}
		else
		{
			return false;
		}
	}
}