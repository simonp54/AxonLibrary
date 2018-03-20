#include "AxonEventTypeNumbers.h"
#include "AxonAFXXLPFrontPanelChangeEvent.h"

#include "AxonDebugDefines.h"

AxonAFXXLPFrontPanelChangeEvent::AxonAFXXLPFrontPanelChangeEvent( )
{
	_groupID = AXON_FAS_FRONT_PANEL_CHANGE_EVENT_TYPE;
}

bool AxonAFXXLPFrontPanelChangeEvent::exactMatch( AxonEvent *event )
{
#ifdef DEBUG_FAS_FRONT_PANEL_CHANGE_EVENT_TYPE
	Serial.println( F("AxonAFXXLPFrontPanelChangeEvent::exactMatch") );
	Serial.println( F("AxonAFXXLPFrontPanelChangeEvent::sameType") );
#endif
	return sameType( event );
}