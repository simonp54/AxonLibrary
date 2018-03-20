#include "AxonAFXXLPPresetBlocksDataRequestAction.h"
#include "AxonMidi.h"
#include "Arduino.h"

const uint8_t AxonAFXXLPPresetBlocksDataRequestAction::_payload[] = { 0x00, 0x01, 0x74, 0x07, 0x0E, 0x0C };	// storage for the request payload

void AxonAFXXLPPresetBlocksDataRequestAction::execute(AxonEvent *event)													// use the midi implementation to send the program change
{
	AxonMidi::instance()->sendSysEx( _network, sizeof( _payload ), _payload, false );
	
#ifdef DEBUG_AXE_FX_XL_PLUS_PRESET_BLOCKS_DATA_REQUEST_ACTION
	Serial.println( F("AxonAFXXLPPresetBlocksDataRequestAction::Sending PresetBlocksData Request") );
#endif
}