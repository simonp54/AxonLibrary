/* originally by Simon Peace
 * AxeFX Preset Store Action
 * VERSION 1.0 11/03/2018
 */
#ifndef AXON_STORE_AXEFX_PRESET_NUMBER_ACTION_h
#define AXON_STORE_AXEFX_PRESET_NUMBER_ACTION_h

#include "AxonAction.h"
#include "AxonEvent.h"

class AxonStoreAxeFXPresetNumberAction: public AxonAction
{
	public:
		void execute(AxonEvent *event);									// the execute method
	protected:
};

#endif