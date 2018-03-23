/* originally by Simon Peace
 * Show the Tuner Screen
 * VERSION 1.0 10/03/2018
 */
#ifndef AXON_SHOWPRESETNAMEACTION_h
#define AXON_SHOWPRESETNAMEACTION_h

#include "AxonEvent.h"
#include "AxonAction.h"

class AxonShowPresetNameAction: public AxonAction
{
	public:
		void execute( AxonAction *sender, AxonEvent *event);									// the execute method
	protected:
};

#endif