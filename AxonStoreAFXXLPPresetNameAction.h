/* originally by Simon Peace
 * AFX Preset Store Action
 * VERSION 1.0 11/03/2018
 */
#ifndef AXON_STORE_AXEFX_PRESET_NAME_ACTION_h
#define AXON_STORE_AXEFX_PRESET_NAME_ACTION_h

#include "AxonAction.h"
#include "AxonEvent.h"

class AxonStoreAFXXLPPresetNameAction: public AxonAction
{
	public:
		void execute( AxonAction *sender, AxonEvent *event);									// the execute method
	protected:
};

#endif