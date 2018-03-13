/* originally by Simon Peace
 * Touch Screen Contrast Up Action
 * VERSION 1.0 10/03/2018
 */
#ifndef AXON_CONTRAST_UP_ACTION_h
#define AXON_CONTRAST_UP_ACTION_h

#include "AxonAction.h"
#include "Arduino.h"

class AxonContrastUpAction: public AxonAction							// Midi base Action class derived from AxonAction
{
	public:
		void execute(AxonEvent *event);									// the execute method
	protected:
};

#endif