#ifndef AXONFASFRONTPANELCHANGEEVENT_h
#define AXONFASFRONTPANELCHANGEEVENT_h

#include "AxonFASEvent.h"
#include "AxonEvent.h"

class AxonFASFrontPanelChangeEvent: public AxonFASEvent
{
	public:
		AxonFASFrontPanelChangeEvent( );

		bool exactMatch( AxonEvent *event );
	protected:
};

#endif