#include "AxonSwitchEvent.h"
#include "AxonEventTypeNumbers.h"
#include "Arduino.h"

#include "AxonDebugDefines.h"

AxonSwitchEvent::AxonSwitchEvent( uint8_t switchNumber )
{
	_groupID = AXON_SWITCH_EVENT_TYPE;
	_switchNumber = switchNumber;
}

bool AxonSwitchEvent::exactMatch( AxonEvent *event )
{
#ifdef DEBUG_AXON_SWITCH_EVENT
	Serial.println( F("AxonSwitchEvent::exactMatch") );
	Serial.println( F("AxonSwitchEvent::sameType") );
#endif
	if (sameType(event))
	{
#ifdef DEBUG_AXON_SWITCH_EVENT
		Serial.println( F(" Group matches") );
#endif
		AxonSwitchEvent *tmp = event;
		if (tmp->getSwitchNumber() == _switchNumber)
		{
#ifdef DEBUG_AXON_SWITCH_EVENT
			Serial.print( _groupID );
			Serial.print( F(":") );
			Serial.println( _switchNumber );
			Serial.println( F(" switchNumber matches (AKA EXACTMATCH)") );
#endif
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}