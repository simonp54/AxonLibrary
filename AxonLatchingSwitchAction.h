/*
 * AxonLatchingSwitchAction - an object that watches a switch "Subject"... and executes configured commands for "on" and "off"
 */
#ifndef AXON_LATCHING_SWITCH_ACTION_h
#define AXON_LATCHING_SWITCH_ACTION_h

#include "AxonAction.h"
#include "AxonHardwareSwitchEvent.h"
#include "AxonMultiOnOffChangeAction.h"

class AxonLatchingSwitchAction : public AxonMultiOnOffChangeAction
{
	public:
		AxonLatchingSwitchAction();
		~AxonLatchingSwitchAction();
		
		void execute( AxonAction *sender, AxonEvent *event );
	private:
		bool _switchState = false;
		bool _ignoreSubsequentDown = false;
};

#endif