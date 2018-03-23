/*
 * AxonMomentarySwitchAction  takes hardwareSwitchEvents and turns them into Software Switch Events
 */
#ifndef AXON_MOMENTARY_SWITCH_ACTION_h
#define AXON_MOMENTARY_SWITCH_ACTION_h

#include "AxonAction.h" 

class AxonMomentarySwitchAction : public AxonAction
{
	public:
		AxonMomentarySwitchAction();
		~AxonMomentarySwitchAction();

		void setOnAction( AxonAction *action ) { _onAction = action; }
		void setOffAction( AxonAction *action ) { _offAction = action; }
		
		void setInterval( uint16_t interval );
		uint16_t getInterval();
		void execute( AxonAction *sender, AxonEvent *event );
	private:
		bool _switchState = false;
		uint64_t _startMillis = 0;
		uint16_t _interval = 0;

		AxonAction *_onAction = 0;
		AxonAction *_offAction = 0;
};

#endif