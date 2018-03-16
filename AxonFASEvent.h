#ifndef AXONFASEVENT_h
#define AXONFASEVENT_h

#include "AxonEvent.h"

class AxonFASEvent: public AxonEvent
{
	public:
		AxonFASEvent( );

		bool exactMatch( AxonEvent *event );
	protected:
};

#endif