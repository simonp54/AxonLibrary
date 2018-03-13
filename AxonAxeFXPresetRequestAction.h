/* originally by Simon Peace
 * Send Midi BANK SELECT and subsequent Program Change to select AxeFX Preset Action Class
 * VERSION 1.0 11/03/2018
 */
#ifndef AXON_AXEFX_PRESET_REQUEST_ACTION_h
#define AXON_AXEFX_PRESET_REQUEST_ACTION_h

#include "AxonMidiChannelBasedAction.h"
#include "AxonEvent.h"

class AxonAxeFXPresetRequestAction: public AxonMidiChannelBasedAction
{
	public:
		void execute(AxonEvent *event);									// the execute method
	private:
		static const uint8_t _BANK_SELECT_MIDI_SPEC = 0;
		uint16_t _currentBank = 0xFF;   // initialised to way outside what the AxeFX has for first time setting

};

#endif