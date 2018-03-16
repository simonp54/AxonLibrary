/* originally by Simon Peace
 * object wrapping MIDI library Class
 * VERSION 1.0 11/03/2018
 */
#ifndef AXON_MIDI_IMPL_2_h
#define AXON_MIDI_IMPL_2_h

#include "AxonMidiWrap.h"
#include "Arduino.h"

class AxonMidiImpl2: public AxonMidiWrap
{
	public:
		AxonMidiImpl2();
	
		void sendCC( uint8_t channel, uint8_t cc, uint8_t val );
		void sendPC( uint8_t channel, uint8_t pc );
		void sendSysEx( uint8_t inLength, const uint8_t* inArray, bool inArrayContainsBoundaries );

		void read();
	protected:
	private:
		static void HandlePC( uint8_t channel, uint8_t pc );
		static void HandleCC( uint8_t channel, uint8_t cc, uint8_t val );
		static void HandleSongSelect( uint8_t songNumber );
		static void HandleSysEx(uint8_t* array, uint8_t size);
};

#endif