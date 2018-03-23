/* originally by Simon Peace
 * Touch Screen Contrast Action
 * VERSION 1.0 10/03/2018
 */
#ifndef AXON_SET_CONTRAST_ACTION_h
#define AXON_SET_CONTRAST_ACTION_h

#include "AxonAction.h"

class AxonContrastSetAction: public AxonAction							
{
	public:
		void execute( AxonAction *sender, AxonEvent *event);									// the execute method
};

#endif