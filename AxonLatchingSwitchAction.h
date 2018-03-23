/*
 * AxonLatchingSwitchAction - an object that watches a switch "Subject"... and executes configured commands for "on" and "off"
 */
#ifndef AXON_LATCHING_SWITCH_ACTION_h
#define AXON_LATCHING_SWITCH_ACTION_h

#include "AxonAction.h"
#include "AxonHardwareSwitchEvent.h"

class AxonLatchingSwitchAction : public AxonAction
{
	public:
		AxonLatchingSwitchAction();
		~AxonLatchingSwitchAction();
		
		void setOnAction( AxonAction *action ) { _onAction = action; }
		void setOffAction( AxonAction *action ) { _offAction = action; }

		void execute( AxonAction *sender, AxonEvent *event );
	private:
		bool _switchState = false;
		bool _ignoreSubsequentDown = false;
		
		AxonAction *_onAction = 0;
		AxonAction *_offAction = 0;
};

#endif