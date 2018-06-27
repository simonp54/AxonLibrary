/*
 * AxonLatchingSwitchLogicBlock
 */
#ifndef AXON_LATCHING_SWITCH_LOGIC_BLOCK_h
#define AXON_LATCHING_SWITCH_LOGIC_BLOCK_h

#include "AxonAction.h"
#include "AxonHardwareSwitchEvent.h"
#include "AxonLogicBlock.h"

class AxonLatchingSwitchLogicBlock : public AxonLogicBlock
{
	public:
		AxonLatchingSwitchLogicBlock();
		~AxonLatchingSwitchLogicBlock();
		
		void execute( AxonAction *sender, AxonEvent *event );
	private:
		bool _switchState = false;
		bool _ignoreSubsequentDown = false;
};

#endif