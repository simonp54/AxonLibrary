/* originally by Simon Peace
 * Show the Tuner Screen
 * VERSION 1.0 10/03/2018
 */
#ifndef AXON_SHOWTUNERSCREENACTION_h
#define AXON_SHOWTUNERSCREENACTION_h

#include "AxonAction.h"
#include "Arduino.h"

class AxonShowTunerScreenAction: public AxonAction							// Midi base Action class derived from AxonAction
{
	public:
		void execute(AxonEvent *event);									// the execute method
	protected:
};

#endif