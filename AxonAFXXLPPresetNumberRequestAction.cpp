/* originally by Simon Peace
 * Send Midi BANK SELECT and subsequent Program Change to select AFX Preset Action Class
 * VERSION 1.0 11/03/2018
 */
#include "AxonAFXXLPPresetNumberRequestAction.h"
#include "AxonGeneralStorage.h"
#include "AxonMidi.h"
#include "Arduino.h"

void AxonAFXXLPPresetNumberRequestAction::execute( AxonAction *sender, AxonEvent *event)													// use the midi implementation to send the program change
{
	uint16_t pcNumber = AxonGeneralStorage::instance()->readAFXXLPPresetNumber();
	
	//To convert the decimal preset number into a Bank/Preset set. This number ranges from 0 to 383 on the Axe FX II, 0 to 767 on the XL/+ and 0 to 511 on the AX8
	//Axe FX II or later, where x is the decimal number from 0 to 383/767
	uint8_t bankNumber = floor(pcNumber / 128); // banks are labeled A,B,C,D,E,F where bank A is 0 and bank F is 5

	uint8_t presetNumber = pcNumber - (bankNumber * 128); // preset number with index of 0, to display offset it to 1 just add 1 to this number when displayed

	if ( (_network != 0xFF) && (_channel != 0xFF) )
	{
		if (_currentBank != bankNumber)
		{
			_currentBank = bankNumber;
			AxonMidi::instance()->sendCC( _network, _channel, _BANK_SELECT_MIDI_SPEC, bankNumber );
		}
		
		AxonMidi::instance()->sendPC( _network, _channel, presetNumber );
	}	
#ifdef DEBUG_WARNINGS
	else
	{
		Serial.println( F("Axon AFX Preset Request Action tried to Execute without valid parameters") );
	}
#endif
}