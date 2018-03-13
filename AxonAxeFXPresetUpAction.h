/* originally by Simon Peace
 * AxeFX Preset Up Action
 * VERSION 1.0 11/03/2018
 */
#ifndef AXON_AXEFX_PRESET_UP_ACTION_h
#define AXON_AXEFX_PRESET_UP_ACTION_h

#include "AxonAction.h"
#include "Arduino.h"

class AxonAxeFXPresetUpAction: public AxonAction							// Midi base Action class derived from AxonAction
{
	public:
		void execute(AxonEvent *event);									// the execute method
	protected:
};

#endif