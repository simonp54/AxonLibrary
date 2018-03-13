/* originally by Simon Peace
 * Base object wrapping Class
 * VERSION 1.0 19/02/2018
 */
#ifndef AXON_MIDI_h
#define AXON_MIDI_h

#include "AxonMidiWrap.h"
#include "Arduino.h"

class AxonMidi										// this is really just a place holder, but may well end up wrapping the MIDI library
{
	public:
		static AxonMidi *instance();		// accessor method
		
		void sendCC( uint8_t network, uint8_t channel, uint8_t cc, uint8_t val );
		void sendPC( uint8_t network, uint8_t channel, uint8_t pc );
		void read();
	protected:
		AxonMidi();
	private:
		static AxonMidi *_instance;

		AxonMidiWrap *_midiNet[2];
};

#endif