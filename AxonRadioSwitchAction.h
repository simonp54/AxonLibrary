#ifndef AXON_RADIO_SWITCH_ACTION_h
#define AXON_RADIO_SWITCH_ACTION_h

#include "AxonAction.h" 

class AxonRadioSwitchAction : public AxonAction
{
	public:
		AxonRadioSwitchAction();
		~AxonRadioSwitchAction();

		void setOnAction( AxonAction *action ) { _onAction = action; }
		void setOffAction( AxonAction *action ) { _offAction = action; }
		void setChangeAction( AxonAction *action ) { _changeAction = action; }
		
		void execute( AxonAction *sender, AxonEvent *event );
	private:
		bool processHardwareSwitchEventStyle( AxonAction *sender, AxonEvent *event );
		bool processSoftwareSwitchEventStyle( AxonAction *sender, AxonEvent *event );
		bool _switchState = false;

		AxonAction *_onAction = 0;
		AxonAction *_offAction = 0;
		AxonAction *_changeAction = 0;
};

#endif