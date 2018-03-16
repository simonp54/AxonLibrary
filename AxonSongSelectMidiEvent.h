#ifndef AXON_SONGSELECT_MIDI_EVENT_h
#define AXON_SONGSELECT_MIDI_EVENT_h

#include "Arduino.h"
#include "AxonMidiEvent.h"

class AxonSongSelectMidiEvent: public AxonMidiEvent
{
	public:
		AxonSongSelectMidiEvent();

		uint8_t getSongNumber() { return _songNumber; }
		void setSongNumber(uint8_t songNumber) { _songNumber = songNumber; }
		
		virtual bool exactMatch( AxonEvent *event );
	protected:
		uint8_t _songNumber = 0;
};

#endif