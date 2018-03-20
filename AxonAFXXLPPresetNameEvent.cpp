#include "AxonEventTypeNumbers.h"
#include "AxonAFXXLPPresetNameEvent.h"

#include "AxonDebugDefines.h"

AxonAFXXLPPresetNameEvent::AxonAFXXLPPresetNameEvent( )
{
	_groupID = AXON_FAS_PRESET_NAME_EVENT_TYPE;
}

const char *AxonAFXXLPPresetNameEvent::getPresetName()
{
	return _presetName;
}

void AxonAFXXLPPresetNameEvent::setPresetName( const char *name )
{
	strncpy( _presetName, name, AxonGeneralStorage::AXEFX_PRESET_NAME_MAXIMUM_SIZE );
	_presetName[ AxonGeneralStorage::AXEFX_PRESET_NAME_MAXIMUM_SIZE ] = '\0';
}

bool AxonAFXXLPPresetNameEvent::exactMatch( AxonEvent *event )
{
#ifdef DEBUG_FAS_PRESET_NUMBER_EVENT_TYPE;
	Serial.println( F("AxonAFXXLPPresetNameEvent::exactMatch") );
	Serial.println( F("AxonAFXXLPPresetNameEvent::sameType") );
#endif
	if (sameType(event))
	{
#ifdef DEBUG_FAS_PRESET_NUMBER_EVENT_TYPE
		Serial.println( F(" Group matches") );
#endif
		AxonAFXXLPPresetNameEvent *tmp = event;
		
		if (strncmp( tmp->getPresetName(), _presetName, AxonGeneralStorage::AXEFX_PRESET_NAME_MAXIMUM_SIZE ) == 0)
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