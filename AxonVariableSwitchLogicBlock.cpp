/*
 * AxonVariableSwitchLogicBlock
 */
#include "AxonVariableSwitchLogicBlock.h"
#include "AxonHardwareSwitchEvent.h"
#include "AxonSoftwareSwitchEvent.h"
#include "Arduino.h"

#include "AxonDebugDefines.h"
#include "AxonCheckMem.h"


AxonVariableSwitchLogicBlock::AxonVariableSwitchLogicBlock()
{
#ifdef DEBUG_VARIABLE_SWITCH_ACTION
	Serial.println( F("AxonVariableSwitchLogicBlock::ctor") );
#endif
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
}

AxonVariableSwitchLogicBlock::~AxonVariableSwitchLogicBlock()
{
#ifdef DEBUG_VARIABLE_SWITCH_ACTION
	Serial.println( F("AxonVariableSwitchLogicBlock::dtor") );
#endif
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
}

void AxonVariableSwitchLogicBlock::execute( AxonAction *sender, AxonEvent *event )
{
#ifdef DEBUG_VARIABLE_SWITCH_ACTION
	Serial.print( F("AxonVariableSwitchLogicBlock::event         received:") );
	Serial.println( event->getGroupID() );
#endif
	AxonHardwareSwitchEvent *tmp = new AxonHardwareSwitchEvent( 0 );		// switch number not important for subsequent check

	if (event->sameType(tmp))
	{
#ifdef DEBUG_VARIABLE_SWITCH_ACTION
		Serial.print( F("AxonVariableSwitchLogicBlock::event ") );
		Serial.println( F("is a hardware switch type") );
#endif		
		AxonHardwareSwitchEvent *tmp2 = event;											// this is now safe to do!	
	
		AxonSoftwareSwitchEvent *swEvent = new AxonSoftwareSwitchEvent(tmp2->getSwitchNumber());
		swEvent->setVal( tmp2->getVal() );
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
#ifdef DEBUG_VARIABLE_SWITCH_ACTION
		Serial.print( F("AxonVariableSwitchLogicBlock::event ") );
		Serial.print( F("creating Software Switch Event ") );
#endif
		executeChangeActions( this, swEvent );

		delete swEvent;
	}
	
	delete tmp;
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
}