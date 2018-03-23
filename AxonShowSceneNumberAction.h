#ifndef AXON_SHOWSCENENUMBERACTION_h
#define AXON_SHOWSCENENUMBERACTION_h

#include "AxonEvent.h"
#include "AxonAction.h"

class AxonShowSceneNumberAction: public AxonAction
{
	public:
		void execute( AxonAction *sender, AxonEvent *event);									// the execute method
	protected:
};

#endif