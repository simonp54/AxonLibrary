#include "AxonAFXXLPSceneNumberRequestAction.h"
#include "AxonMidi.h"
#include "Arduino.h"

const uint8_t AxonAFXXLPSceneNumberRequestAction::_payload[] = { 0xF0, 0x00, 0x01, 0x74, 0x07, 0x29, 0x7F, 0x54, 0xF7 };	// storage for the request payload

void AxonAFXXLPSceneNumberRequestAction::execute( AxonAction *sender, AxonEvent *event)													// use the midi implementation to send the program change
{
	AxonMidi::instance()->sendSysEx( _network, sizeof( _payload ), _payload, false );
	
	Serial.println( F("AxonAFXXLPSceneNumberRequestAction::Sending Scene Number Request") );
}