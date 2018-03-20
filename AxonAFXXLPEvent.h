#ifndef AXONFASEVENT_h
#define AXONFASEVENT_h

#include "AxonEvent.h"

class AxonAFXXLPEvent: public AxonEvent
{
	public:
		AxonAFXXLPEvent( );

		bool exactMatch( AxonEvent *event );
	protected:
};

#endif