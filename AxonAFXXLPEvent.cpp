#include "AxonEventTypeNumbers.h"
#include "AxonAFXXLPEvent.h"

#include "AxonDebugDefines.h"

AxonAFXXLPEvent::AxonAFXXLPEvent( )
{
	_groupID = AXON_FAS_EVENT_TYPE;
}

bool AxonAFXXLPEvent::exactMatch( AxonEvent *event )
{
#ifdef DEBUG_AXEFX_XL_PLUS_FRONT_PANEL_CHANGE_EVENT_TYPE
	Serial.println( F("AxonAFXXLPEvent::exactMatch") );
	Serial.println( F("AxonAFXXLPEvent::sameType") );
#endif
	return sameType( event );
}