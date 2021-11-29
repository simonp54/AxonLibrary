#include "AxonEventTypeNumbers.h"
#include "AxonEvent.h"

#include "AxonDebugDefines.h"

AxonEvent::AxonEvent( )
{
	// _groupID = AXON_EVENT_TYPE;
}

// bool AxonEvent::sameType( AxonEvent *event )
// {
// 	if ((event->getGroupID() & _groupID) == event->getGroupID())
// 	{
// #ifdef DEBUG_EVENT
// 		Serial.print( F(" matching ") );
// 		Serial.print( event->getGroupID(), BIN );
// 		Serial.print( F(" vs ") );
// 		Serial.print( _groupID, BIN );
// 		Serial.print( F(" ") );	
// 		Serial.println( F("SAME TYPE") );
// #endif
// 		return true;
// 	}
// 	else
// 	{
// #ifdef DEBUG_EVENT_VERBOSE
// 		Serial.print( F(" matching ") );
// 		Serial.print( event->getGroupID(), BIN );
// 		Serial.print( F(" vs ") );
// 		Serial.print( _groupID, BIN );
// 		Serial.print( F(" ") );	
// 		Serial.println( F("DIFFERENT TYPE") );
// #endif
// 		return false;
// 	}
// }

// bool AxonEvent::exactMatch( AxonEvent *event )
// {
// #ifdef DEBUG_EVENT
// 	Serial.println( F("AxonEvent::exactMatch") );
// 	Serial.print( F("AxonEvent::sameType") );
// #endif
// 	return sameType( event );
// }