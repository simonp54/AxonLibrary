#include "AxonAxeFXXLPlusSceneNumberRequestAction.h"
#include "AxonMidi.h"
#include "Arduino.h"

const uint8_t AxonAxeFXXLPlusSceneNumberRequestAction::_payload[] = { 0xF0, 0x00, 0x01, 0x74, 0x07, 0x29, 0x7F, 0x54, 0xF7 };	// storage for the request payload

void AxonAxeFXXLPlusSceneNumberRequestAction::execute(AxonEvent *event)													// use the midi implementation to send the program change
{
	AxonMidi::instance()->sendSysEx( _network, sizeof( _payload ), _payload, false );
	
	Serial.println( F("AxonAxeFXXLPlusSceneNumberRequestAction::Sending Scene Number Request") );
}