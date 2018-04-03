/*
 * AxonMomentarySwitchAction  takes hardwareSwitchEvents and turns them into Software Switch Events
 */
#ifndef AXON_MOMENTARY_SWITCH_ACTION_h
#define AXON_MOMENTARY_SWITCH_ACTION_h

#include "AxonMultiOnOffChangeAction.h"

class AxonMomentarySwitchAction : public AxonMultiOnOffChangeAction
{
	public:
		AxonMomentarySwitchAction();
		~AxonMomentarySwitchAction();
		
		void setInterval( uint16_t interval );
		uint16_t getInterval();
		void execute( AxonAction *sender, AxonEvent *event );
	private:
		bool _switchState = false;
		uint64_t _startMillis = 0;
		uint16_t _interval = 0;
};

#endif