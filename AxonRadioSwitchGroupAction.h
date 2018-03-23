#ifndef AXON_RADIO_GROUP_SWITCH_ACTION_h
#define AXON_RADIO_GROUP_SWITCH_ACTION_h

#include "AxonAction.h" 
#include "AxonHardwareSwitchEvent.h"

class AxonRadioSwitchGroupAction : public AxonAction
{
	public:
		AxonRadioSwitchGroupAction();
		~AxonRadioSwitchGroupAction();
		
		void setChangeAction( AxonAction *action ) { _changeAction = action; }
		
		void addSwitch( AxonAction *action );
		void removeSwitch( AxonAction *action );
	
		void execute( AxonAction *sender, AxonEvent *event );
	private:
		bool processSoftwareSwitchEventStyle( AxonAction *sender, AxonEvent *event );
		bool processAFXXLPSceneNumberEventStyle( AxonAction *sender, AxonEvent *event );

		static const uint8_t _MAX_GROUP_SIZE = 24;
		
		uint8_t _switchListCount = 0;
		AxonAction *_switchList[_MAX_GROUP_SIZE] = {0};
		uint8_t _lastIndexOn = _MAX_GROUP_SIZE + 1;
		
		AxonAction *_changeAction = 0;
};

#endif