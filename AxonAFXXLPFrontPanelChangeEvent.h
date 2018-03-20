#ifndef AXONFASFRONTPANELCHANGEEVENT_h
#define AXONFASFRONTPANELCHANGEEVENT_h

#include "AxonAFXXLPEvent.h"
#include "AxonEvent.h"

class AxonAFXXLPFrontPanelChangeEvent: public AxonAFXXLPEvent
{
	public:
		AxonAFXXLPFrontPanelChangeEvent( );

		bool exactMatch( AxonEvent *event );
	protected:
};

#endif