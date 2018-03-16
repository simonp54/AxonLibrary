#include "AxonAxeFXXLPlusPresetBlocksDataRequestAction.h"
#include "AxonMidi.h"
#include "Arduino.h"

const uint8_t AxonAxeFXXLPlusPresetBlocksDataRequestAction::_payload[] = { 0x00, 0x01, 0x74, 0x07, 0x0E, 0x0C };	// storage for the request payload

void AxonAxeFXXLPlusPresetBlocksDataRequestAction::execute(AxonEvent *event)													// use the midi implementation to send the program change
{
	AxonMidi::instance()->sendSysEx( _network, 6, _payload, false );
	
	Serial.println( F("AxonAxeFXXLPlusPresetBlocksDataRequestAction::Sending PresetBlocksData Request") );
}