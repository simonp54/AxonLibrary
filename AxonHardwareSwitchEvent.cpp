#include "AxonHardwareSwitchEvent.h"
#include "AxonEventTypeNumbers.h"
#include "Arduino.h"

AxonHardwareSwitchEvent::AxonHardwareSwitchEvent( uint8_t switchNumber ) : AxonSwitchEvent(switchNumber)
{
	_groupID = AXON_HARDWARE_SWITCH_EVENT_TYPE;
}