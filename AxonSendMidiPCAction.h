/* originally by Simon Peace
 * Midi Program Change Action Class
 * VERSION 1.0 19/02/2018
 */
#ifndef AXON_SEND_MIDI_PC_ACTION_h
#define AXON_SEND_MIDI_PC_ACTION_h

#include "AxonMidiChannelBasedAction.h"
#include "Arduino.h"

class AxonSendMidiPCAction: public AxonMidiChannelBasedAction			// Midi Program Change Action class derived from AxonAction
{
	public:
		void setPC( uint8_t PC );
		void execute( AxonAction *sender, AxonEvent *event);									// the execute method
	private:
		uint8_t _pc = 0xFF;												// storage for the program change number
};

#endif