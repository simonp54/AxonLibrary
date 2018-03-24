
#ifndef AXON_U2BABY_MEMORY_MAP_ACTION_h
#define AXON_U2BABY_MEMORY_MAP_ACTION_h

#include "AxonAction.h"
#include "Arduino.h"

class AxonU2BabyMemoryMapAction: public AxonAction							// Midi base Action class derived from AxonAction
{
	public:
		void execute( AxonAction *sender, AxonEvent *event);									// the execute method
	protected:
};

#endif