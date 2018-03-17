#include "AxonFASTunerInfoEvent.h"
#include "AxonEventTypeNumbers.h"

#include "AxonDebugDefines.h"

AxonFASTunerInfoEvent::AxonFASTunerInfoEvent( )
{
	_groupID = AXON_FAS_TUNER_INFO_EVENT_TYPE;
}

bool AxonFASTunerInfoEvent::exactMatch( AxonEvent *event )
{
#ifdef DEBUG_FAS_TUNER_INFO_EVENT_TYPE;
	Serial.println( F("AxonFASTunerInfoEvent::exactMatch") );
	Serial.println( F("AxonFASTunerInfoEvent::sameType") );
#endif
	if (sameType(event))
	{
#ifdef DEBUG_FAS_TUNER_INFO_EVENT_TYPE
		Serial.println( F(" Group matches") );
#endif
		AxonFASTunerInfoEvent *tmp = event;
		
		if ( (tmp->getNote() == _note) && (tmp->getString() == _string) && (tmp->getData() == _data) )
		{
#ifdef DEBUG_FAS_TUNER_INFO_EVENT_TYPE
			Serial.print( _groupID );
			Serial.print( F(":") );
			Serial.print( _note );
			Serial.print( F(":") );
			Serial.print( _string );
			Serial.print( F(":") );
			Serial.println( _data );
			Serial.println( F(" note,string,data match (AKA EXACTMATCH)") );
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