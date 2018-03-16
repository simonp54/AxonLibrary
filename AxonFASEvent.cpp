#include "AxonEventTypeNumbers.h"
#include "AxonFASEvent.h"

#include "AxonDebugDefines.h"

AxonFASEvent::AxonFASEvent( )
{
	_groupID = AXON_FAS_EVENT_TYPE;
}

bool AxonFASEvent::exactMatch( AxonEvent *event )
{
#ifdef DEBUG_AXON_AXEFX_XL_PLUS_FRONT_PANEL_CHANGE_EVENT_TYPE
	Serial.println( F("AxonFASEvent::exactMatch") );
	Serial.println( F("AxonFASEvent::sameType") );
#endif
	return sameType( event );
}