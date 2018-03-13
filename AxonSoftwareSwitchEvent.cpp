#include "AxonSoftwareSwitchEvent.h"
#include "AxonEventTypeNumbers.h"
#include "Arduino.h"

AxonSoftwareSwitchEvent::AxonSoftwareSwitchEvent( uint8_t switchNumber ) : AxonSwitchEvent( switchNumber )
{
	_groupID = AXON_SOFTWARE_SWITCH_EVENT_TYPE;
}