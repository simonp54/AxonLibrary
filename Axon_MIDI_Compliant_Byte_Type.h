#ifndef AXON_MIDI_COMPLIANT_BYTE_TYPE_h
#define AXON_MIDI_COMPLIANT_BYTE_TYPE_h

#include "Arduino.h"

class AxonMidiCompliantByteType
{
	public:
		uint8_t get() { return _val; }
		void set( uint8_t val )
			{ if( val >= MAX_VALUE) {_val = MAX_VALUE; return;}
			  if( val <= MIN_VALUE) {_val = MIN_VALUE; return;}
			  _val = val; }
	private:
		uint8_t _val;

		static const uint8_t MAX_VALUE = 127;
		static const uint8_t MIN_VALUE = 0;
};

#endif