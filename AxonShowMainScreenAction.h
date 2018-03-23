/* originally by Simon Peace
 * Show the Tuner Screen
 * VERSION 1.0 10/03/2018
 */
#ifndef AXON_SHOWMAINSCREENACTION_h
#define AXON_SHOWMAINSCREENACTION_h

#include "AxonAction.h"
#include "Arduino.h"

class AxonShowMainScreenAction: public AxonAction							// Midi base Action class derived from AxonAction
{
	public:
		void execute( AxonAction *sender, AxonEvent *event);									// the execute method
	protected:
};

#endif