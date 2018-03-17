#include "AxonAxeFXXLPlusPresetNameRequestAction.h"
#include "AxonMidi.h"
#include "Arduino.h"

const uint8_t AxonAxeFXXLPlusPresetNameRequestAction::_payload[] = { 0xF0, 0x00, 0x01, 0x74, 0x07, 0x0F, 0x0D, 0xF7 };	// storage for the request payload

void AxonAxeFXXLPlusPresetNameRequestAction::execute(AxonEvent *event)													// use the midi implementation to send the program change
{
	AxonMidi::instance()->sendSysEx( _network, sizeof( _payload ), _payload, false );
	
#ifdef DEBUG_AXON_AXE_FX_XL_PLUS_PRESET_NAME_REQUEST_ACTION
	Serial.println( F("AxonAxeFXXLPlusPresetNameRequestAction::Sending PresetName Request") );
#endif
}