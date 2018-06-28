/* originally by Simon Peace
 * Next Surface Action
 * VERSION 1.0 28/06/2018
 */
#ifndef AXON_NEXT_SURFACE_ACTION_h
#define AXON_NEXT_SURFACE_ACTION_h

#include "AxonAction.h"

class AxonNextSurfaceAction: public AxonAction							// Midi base Action class derived from AxonAction
{
	public:
		void execute( AxonAction *sender, AxonEvent *event);									// the execute method
};

#endif