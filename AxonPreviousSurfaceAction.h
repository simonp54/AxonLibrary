/* originally by Simon Peace
 * Previous Surface Action
 * VERSION 1.0 28/06/2018
 */
#ifndef AXON_PREVIOUS_SURFACE_ACTION_h
#define AXON_PREVIOUS_SURFACE_ACTION_h

#include "AxonAction.h"

class AxonPreviousSurfaceAction: public AxonAction
{
	public:
		void execute( AxonAction *sender, AxonEvent *event);									// the execute method
};

#endif