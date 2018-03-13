#include "AxonEventTypeNumbers.h"
#include "AxonEvent.h"

#include "AxonDebugDefines.h"

AxonEvent::AxonEvent( )
{
	_groupID = AXON_EVENT_TYPE;
}

bool AxonEvent::sameType( AxonEvent *event )
{
#ifdef DEBUG_AXON_EVENT
	Serial.print( F(" matching ") );
	Serial.print( event->getGroupID(), BIN );
	Serial.print( F(" vs ") );
	Serial.print( _groupID, BIN );
	Serial.print( F(" ") );	
	(( event->getGroupID() & _groupID) == event->getGroupID()) ? Serial.println( F("MATCH") ): Serial.println( );
#endif
	
	if ((event->getGroupID() & _groupID) == event->getGroupID())
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool AxonEvent::exactMatch( AxonEvent *event )
{
#ifdef DEBUG_AXON_EVENT
	Serial.println( F("AxonEvent::exactMatch") );
	Serial.print( F("AxonEvent::sameType") );
#endif
	return sameType( event );
}