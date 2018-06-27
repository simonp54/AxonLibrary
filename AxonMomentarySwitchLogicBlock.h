/*
 * AxonMomentarySwitchLogicBlock  takes hardwareSwitchEvents and turns them into Software Switch Events
 */
#ifndef AXON_MOMENTARY_SWITCH_LOGIC_BLOCK_h
#define AXON_MOMENTARY_SWITCH_LOGIC_BLOCK_h

#include "AxonLogicBlock.h"

class AxonMomentarySwitchLogicBlock : public AxonLogicBlock
{
	public:
		AxonMomentarySwitchLogicBlock();
		~AxonMomentarySwitchLogicBlock();
		
		void setInterval( uint16_t interval );
		uint16_t getInterval();
		void execute( AxonAction *sender, AxonEvent *event );
	private:
		bool _switchState = false;
		uint64_t _startMillis = 0;
		uint16_t _interval = 0;
};

#endif