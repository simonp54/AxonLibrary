#include "AxonEventTypeNumbers.h"
#include "AxonAFXXLPPresetNumberEvent.h"

#include "AxonDebugDefines.h"

AxonAFXXLPPresetNumberEvent::AxonAFXXLPPresetNumberEvent( )
{
	_groupID = AXON_FAS_PRESET_NUMBER_EVENT_TYPE;
}

void AxonAFXXLPPresetNumberEvent::setPresetNumber( uint8_t lsByte, uint8_t msByte )
{
	_presetNumber = (lsByte & 0x7F) | ((msByte & 0x7F) << 7);
}

bool AxonAFXXLPPresetNumberEvent::exactMatch( AxonEvent *event )
{
#ifdef DEBUG_FAS_PRESET_NUMBER_EVENT_TYPE;
	Serial.println( F("AxonAFXXLPPresetNumberEvent::exactMatch") );
	Serial.println( F("AxonAFXXLPPresetNumberEvent::sameType") );
#endif
	if (sameType(event))
	{
#ifdef DEBUG_FAS_PRESET_NUMBER_EVENT_TYPE
		Serial.println( F(" Group matches") );
#endif
		AxonAFXXLPPresetNumberEvent *tmp = event;
		if (tmp->getPresetNumber() == _presetNumber)
		{
#ifdef DEBUG_FAS_PRESET_NUMBER_EVENT_TYPE
			Serial.print( _groupID );
			Serial.print( F(":") );
			Serial.println( _presetNumber );
			Serial.println( F(" presetNumber matches (AKA EXACTMATCH)") );
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