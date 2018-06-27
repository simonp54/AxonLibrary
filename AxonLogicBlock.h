#ifndef AXON_LOGIC_BLOCK_h
#define AXON_LOGIC_BLOCK_h

#include "AxonEvent.h"
#include "AxonAction.h"
#include "Arduino.h"

class AxonLogicBlock: public AxonAction
{
	public:
		void setOnAction( uint16_t actionNumber );
		void setOffAction( uint16_t actionNumber );
		void setChangeAction( uint16_t actionNumber );
		void executeOnActions( AxonAction *sender, AxonEvent *event );
		void executeOffActions( AxonAction *sender, AxonEvent *event );
		void executeChangeActions( AxonAction *sender, AxonEvent *event );
		
		void clearAllActions();
		
		virtual void execute( AxonAction *sender, AxonEvent *event ) = 0;		// pure virtual function definition of the Execute method (aka doesn't exist here and never will)
	private:
		static const uint8_t _maxActions = 32;
		
		uint16_t _onAction[_maxActions];
		uint16_t _offAction[_maxActions];
		uint16_t _changeAction[_maxActions];
		
		uint8_t _onActionCount = 0;
		uint8_t _offActionCount = 0;
		uint8_t _changeActionCount = 0;
};

#endif