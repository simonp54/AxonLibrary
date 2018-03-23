#ifndef AXON_STORE_AXEFX_SCENE_NUMBER_ACTION_h
#define AXON_STORE_AXEFX_SCENE_NUMBER_ACTION_h

#include "AxonAction.h"
#include "AxonEvent.h"

class AxonStoreAFXXLPSceneNumberAction: public AxonAction
{
	public:
		void execute( AxonAction *sender, AxonEvent *event);									// the execute method
	protected:
};

#endif