/* originally by Simon Peace
 * Show the Tuner Screen
 * VERSION 1.0 10/03/2018
 */
#ifndef AXON_SHOWPRESETNUMBERACTION_h
#define AXON_SHOWPRESETNUMBERACTION_h

#include "AxonEvent.h"
#include "AxonAction.h"

class AxonShowPresetNumberAction: public AxonAction
{
	public:
		void execute(AxonEvent *event);									// the execute method
	protected:
};

#endif