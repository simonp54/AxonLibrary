#ifndef AXON_DISPLAY_BLOCK_h
#define AXON_DISPLAY_BLOCK_h

#include "AxonEvent.h"
#include "AxonAction.h"
#include "Arduino.h"

class AxonDisplayBlock: public AxonAction
{
	public:
		virtual void execute( AxonAction *sender, AxonEvent *event ) = 0;		// pure virtual function definition of the Execute method (aka doesn't exist here and never will)
	private:
};

#endif