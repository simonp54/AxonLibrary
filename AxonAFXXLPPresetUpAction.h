/* originally by Simon Peace
 * AFX Preset Up Action
 * VERSION 1.0 11/03/2018
 */
#ifndef AXON_AXEFX_PRESET_UP_ACTION_h
#define AXON_AXEFX_PRESET_UP_ACTION_h

#include "AxonAction.h"
#include "Arduino.h"

class AxonAFXXLPPresetUpAction: public AxonAction							// Midi base Action class derived from AxonAction
{
	public:
		void execute( AxonAction *sender, AxonEvent *event);									// the execute method
	protected:
};

#endif