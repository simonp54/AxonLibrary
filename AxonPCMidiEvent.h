#ifndef AXON_PC_MIDI_EVENT_h
#define AXON_PC_MIDI_EVENT_h

#include "Arduino.h"
#include "AxonChannelMidiEvent.h"

class AxonPCMidiEvent: public AxonChannelMidiEvent
{
	public:
		AxonPCMidiEvent();

		uint8_t getPC() { return _pc; }
		void setPC(uint8_t pc) { _pc = pc; }

		virtual bool exactMatch( AxonEvent *event );
	private:
		uint8_t _pc = 0;
};

#endif