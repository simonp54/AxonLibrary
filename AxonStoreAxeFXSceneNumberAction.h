#ifndef AXON_STORE_AXEFX_SCENE_NUMBER_ACTION_h
#define AXON_STORE_AXEFX_SCENE_NUMBER_ACTION_h

#include "AxonAction.h"
#include "AxonEvent.h"

class AxonStoreAxeFXSceneNumberAction: public AxonAction
{
	public:
		void execute(AxonEvent *event);									// the execute method
	protected:
};

#endif