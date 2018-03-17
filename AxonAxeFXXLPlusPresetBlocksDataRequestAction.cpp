#include "AxonAxeFXXLPlusPresetBlocksDataRequestAction.h"
#include "AxonMidi.h"
#include "Arduino.h"

const uint8_t AxonAxeFXXLPlusPresetBlocksDataRequestAction::_payload[] = { 0x00, 0x01, 0x74, 0x07, 0x0E, 0x0C };	// storage for the request payload

void AxonAxeFXXLPlusPresetBlocksDataRequestAction::execute(AxonEvent *event)													// use the midi implementation to send the program change
{
	AxonMidi::instance()->sendSysEx( _network, sizeof( _payload ), _payload, false );
	
#ifdef DEBUG_AXON_AXE_FX_XL_PLUS_PRESET_BLOCKS_DATA_REQUEST_ACTION
	Serial.println( F("AxonAxeFXXLPlusPresetBlocksDataRequestAction::Sending PresetBlocksData Request") );
#endif
}