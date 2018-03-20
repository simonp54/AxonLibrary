#include "AxonEventTypeNumbers.h"
#include "AxonAFXXLPSceneNumberEvent.h"

#include "AxonDebugDefines.h"

AxonAFXXLPSceneNumberEvent::AxonAFXXLPSceneNumberEvent( )
{
	_groupID = AXON_FAS_SCENE_NUMBER_EVENT_TYPE;
}

void AxonAFXXLPSceneNumberEvent::setSceneNumber( uint8_t scene )
{
	_sceneNumber = scene;
}

bool AxonAFXXLPSceneNumberEvent::exactMatch( AxonEvent *event )
{
#ifdef DEBUG_FAS_SCENE_NUMBER_EVENT_TYPE
	Serial.println( F("AxonAFXXLPSceneNumberEvent::exactMatch") );
	Serial.println( F("AxonAFXXLPSceneNumberEvent::sameType") );
#endif
	if (sameType(event))
	{
#ifdef DEBUG_FAS_SCENE_NUMBER_EVENT_TYPE
		Serial.println( F(" Group matches") );
#endif
		AxonAFXXLPSceneNumberEvent *tmp = event;
//		if (tmp->getSceneNumber() == _sceneNumber)
//		{
#ifdef DEBUG_FAS_SCENE_NUMBER_EVENT_TYPE
			Serial.print( _groupID );
			Serial.print( F(":") );
			Serial.println( _sceneNumber );
			Serial.println( F(" sceneNumber matches (AKA EXACTMATCH)") );
#endif
			return true;
//		}
//		else
//		{
//			return false;
//		}
	}
	else
	{
		return false;
	}
}