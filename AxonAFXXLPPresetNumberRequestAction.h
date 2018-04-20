/* originally by Simon Peace
 * Send Midi BANK SELECT and subsequent Program Change to select AFX Preset Action Class
 * VERSION 1.0 11/03/2018
 */
#ifndef AXON_AXEFX_PRESET_NUMBER_REQUEST_ACTION_h
#define AXON_AXEFX_PRESET_NUMBER_REQUEST_ACTION_h

#include "AxonMidiChannelBasedAction.h"
#include "AxonEvent.h"

class AxonAFXXLPPresetNumberRequestAction: public AxonMidiChannelBasedAction
{
	public:
		AxonAFXXLPPresetNumberRequestAction( uint8_t network, uint8_t channel ): AxonMidiChannelBasedAction( network, channel ) {};
		void execute( AxonAction *sender, AxonEvent *event);									// the execute method
	private:
		static const uint8_t _BANK_SELECT_MIDI_SPEC = 0;
		uint16_t _currentBank = 0xFF;   // initialised to way outside what the AFX has for first time setting

};

#endif