/* originally by Simon Peace
 * Touch Screen Contrast Action
 * VERSION 1.0 10/03/2018
 */
#ifndef AXON_SET_CONTRAST_ACTION_h
#define AXON_SET_CONTRAST_ACTION_h

#include "AxonAction.h"
#include "Arduino.h"

class AxonSetContrastAction: public AxonAction							
{
	public:
		void execute(AxonEvent *event);									// the execute method
	protected:
};

#endif