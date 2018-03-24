/* originally by Simon Peace
 * Base object wrapping Class
 * VERSION 1.0 19/02/2018
 */
#ifndef AXON_MIDI_h
#define AXON_MIDI_h

#include "AxonMidiWrap.h"
#include "AxonAction.h"
#include "AxonSysExMidiEvent.h"
#include "AxonSongSelectMidiEvent.h"
#include "AxonPCMidiEvent.h"
#include "AxonCCMidiEvent.h"
#include "Arduino.h"

class AxonMidi										// this is really just a place holder, but may well end up wrapping the MIDI library
{
	public:
		static AxonMidi *instance();		// accessor method
		
		void sendCC( uint8_t network, uint8_t channel, uint8_t cc, uint8_t val );
		void sendPC( uint8_t network, uint8_t channel, uint8_t pc );
		void sendSysEx( uint8_t network, uint8_t inLength, const uint8_t* inArray, bool inArrayContainsBoundaries );
		
		void setSysExAction( AxonAction *action ) { _sysExAction = action; }
		void setSongSelectAction( AxonAction *action ) { _songSelectAction = action; }
		void setCCAction( AxonAction *action ) { _ccAction = action; }
		void setPCAction( AxonAction *action ) { _pcAction = action; }
		
		void internal_sysExAction( AxonSysExMidiEvent *event );
		void internal_songSelectAction( AxonSongSelectMidiEvent *event );
		void internal_ccAction( AxonCCMidiEvent *event );
		void internal_pcAction( AxonPCMidiEvent *event );
		
		void read();
	protected:
		AxonMidi();

	private:
		static AxonMidi *_instance;

		AxonMidiWrap *_midiNet[2];
		
		AxonAction *_sysExAction = 0;
		AxonAction *_songSelectAction = 0;
		AxonAction *_ccAction = 0;
		AxonAction *_pcAction = 0;
};

#endif