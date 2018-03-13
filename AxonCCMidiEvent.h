#ifndef AXON_CC_MIDI_EVENT_h
#define AXON_CC_MIDI_EVENT_h

#include "Arduino.h"
#include "AxonChannelMidiEvent.h"

class AxonCCMidiEvent: public AxonChannelMidiEvent
{
	public:
		AxonCCMidiEvent();

		uint8_t getCC() { return _cc; }
		void setCC(uint8_t cc) { _cc = cc; }
		
		uint8_t getVal() { return _val; }
		void setVal(uint8_t val) { _val = val; }

		virtual bool exactMatch( AxonEvent *event );
	private:
		uint8_t _cc = 0;
		uint8_t _val = 0;
};

#endif