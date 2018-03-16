#ifndef AXON_SYSEX_MIDI_EVENT_h
#define AXON_SYSEX_MIDI_EVENT_h

#include "Arduino.h"
#include "AxonMidiEvent.h"

class AxonSysExMidiEvent: public AxonMidiEvent
{
	public:
		AxonSysExMidiEvent();
		virtual ~AxonSysExMidiEvent();
		
		uint8_t getByte( uint8_t pos);
		
		uint8_t getSize() { return _size; }

		virtual void copyData( uint8_t *array, uint8_t size );
		
		virtual bool exactMatch( AxonEvent *event );
	protected:
		void deleteData();

		uint8_t *_array;
		uint8_t _size = 0;
};

#endif