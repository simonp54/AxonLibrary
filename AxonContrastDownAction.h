/* originally by Simon Peace
 * Touch Screen Contrast Down Action
 * VERSION 1.0 10/03/2018
 */
#ifndef AXON_CONTRAST_DOWN_ACTION_h
#define AXON_CONTRAST_DOWN_ACTION_h

#include "AxonAction.h"

class AxonContrastDownAction: public AxonAction							// Midi base Action class derived from AxonAction
{
	public:
		void execute( AxonAction *sender, AxonEvent *event);									// the execute method
};

#endif