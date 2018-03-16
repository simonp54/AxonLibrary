#ifndef AXON_HACKSYSEXEVENTCLIENT_h
#define AXON_HACKSYSEXEVENTCLIENT_h

#include "AxonEventClient.h"
#include "AxonEvent.h"


class AxonHACKSYSEXEventClient : public AxonEventClient
{
	public:
//		void setOnFrontPanelChange( AxonAction *action );
	
		virtual void event( AxonEvent *event );
		
	private:
//		AxonAction *_OnFrontPanelChangeAction = 0;
};

#endif