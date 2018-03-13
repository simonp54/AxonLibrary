#ifndef AXON_CHANNEL_MIDI_EVENT_h
#define AXON_CHANNEL_MIDI_EVENT_h

#include "Arduino.h"
#include "AxonMidiEvent.h"

class AxonChannelMidiEvent: public AxonMidiEvent
{
	public:
		AxonChannelMidiEvent();

		uint8_t getChannel() { return _channel; }
		void setChannel(uint8_t channel) { _channel = channel; }
		
		virtual bool exactMatch( AxonEvent *event );
	protected:
		uint8_t _channel = 0;
};

#endif