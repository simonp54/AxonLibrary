/*
 * AxonVariableSwitchLogicBlock  takes hardwareSwitchEvents and turns them into Software Switch Events
 */
#ifndef AXON_VARIABLE_SWITCH_LOGIC_BLOCK_h
#define AXON_VARIABLE_SWITCH_LOGIC_BLOCK_h

#include "AxonLogicBlock.h"

class AxonVariableSwitchLogicBlock : public AxonLogicBlock
{
	public:
		AxonVariableSwitchLogicBlock();
		~AxonVariableSwitchLogicBlock();
		
		void execute( AxonAction *sender, AxonEvent *event );
	private:
};

#endif