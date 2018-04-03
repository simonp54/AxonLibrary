#ifndef AXON_MULTI_ON_OFF_CHANGE_ACTION_h
#define AXON_MULTI_ON_OFF_CHANGE_ACTION_h

#include "AxonEvent.h"
#include "AxonAction.h"
#include "Arduino.h"

class AxonMultiOnOffChangeAction: public AxonAction						// the generic definition of an AxonAction (doesn't ever exist but is the base type for generic coding)
{
	public:
		void setOnAction( AxonAction *action );
		void setOffAction( AxonAction *action );
		void setChangeAction( AxonAction *action );
		void executeOnActions( AxonAction *sender, AxonEvent *event );
		void executeOffActions( AxonAction *sender, AxonEvent *event );
		void executeChangeActions( AxonAction *sender, AxonEvent *event );
		
		void clearAllActions();
		
		virtual void execute( AxonAction *sender, AxonEvent *event ) = 0;		// pure virtual function definition of the Execute method (aka doesn't exist here and never will)
	private:
		static const uint8_t _maxActions = 36;
		
		AxonAction *_onAction[_maxActions];
		AxonAction *_offAction[_maxActions];
		AxonAction *_changeAction[_maxActions];
		
		uint8_t _onActionCount = 0;
		uint8_t _offActionCount = 0;
		uint8_t _changeActionCount = 0;
};

#endif