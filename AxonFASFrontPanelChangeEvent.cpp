#include "AxonEventTypeNumbers.h"
#include "AxonFASFrontPanelChangeEvent.h"

#include "AxonDebugDefines.h"

AxonFASFrontPanelChangeEvent::AxonFASFrontPanelChangeEvent( )
{
	_groupID = AXON_FAS_FRONT_PANEL_CHANGE_EVENT_TYPE;
}

bool AxonFASFrontPanelChangeEvent::exactMatch( AxonEvent *event )
{
#ifdef DEBUG_FAS_FRONT_PANEL_CHANGE_EVENT_TYPE
	Serial.println( F("AxonFASFrontPanelChangeEvent::exactMatch") );
	Serial.println( F("AxonFASFrontPanelChangeEvent::sameType") );
#endif
	return sameType( event );
}