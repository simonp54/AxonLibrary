/*
 * AxonLatchingSwitchLogicBlock
 */
#include "AxonLatchingSwitchLogicBlock.h"
#include "AxonHardwareSwitchEvent.h"
#include "AxonSoftwareSwitchEvent.h"
#include "Arduino.h"

#include "AxonDebugDefines.h"
#include "AxonCheckMem.h"


AxonLatchingSwitchLogicBlock::AxonLatchingSwitchLogicBlock()
{
#ifdef DEBUG_LATCHING_SWITCH_ACTION
	Serial.println( F("AxonLatchingSwitchLogicBlock::ctor") );
#endif
}

AxonLatchingSwitchLogicBlock::~AxonLatchingSwitchLogicBlock()
{
#ifdef DEBUG_LATCHING_SWITCH_ACTION
	Serial.println( F("AxonLatchingSwitchLogicBlock::dtor") );
#endif
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
}

void AxonLatchingSwitchLogicBlock::execute( AxonAction *sender, AxonEvent *event )
{
#ifdef DEBUG_LATCHING_SWITCH_ACTION
	Serial.print( F("AxonLatchingSwitchLogicBlock::event ") );
	Serial.println( event->getGroupID() );
#endif
	AxonHardwareSwitchEvent *tmp = new AxonHardwareSwitchEvent( 0 );  // switchnumber irrelevant
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif

	if (event->sameType(tmp))
	{
#ifdef DEBUG_LATCHING_SWITCH_ACTION
		Serial.print( F("AxonLatchingSwitchLogicBlock::event ") );
		Serial.println( F("event is a hardware switch type") );
#endif		
		AxonHardwareSwitchEvent *tmp2 = event;	// effectively a type cast to gain access to specific features of this object type
		
#ifdef DEBUG_LATCHING_SWITCH_ACTION
		Serial.print( F("AxonLatchingSwitchLogicBlock::event ") );
		Serial.println( tmp2->getSwitchState() );
#endif		
	
		if ( (_ignoreSubsequentDown == true) && tmp2->getSwitchState() )
		{
			delete tmp;     // THIS IS NOT A DUPLICATE of the delete lower down... but releases the memory correctly
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
			return;														// quickly ignore the "duplicated down notifications"
																		// these are for more complex switch types
		}

		if ( (_switchState == false) && tmp2->getSwitchState() )			// transission to "down from off"
		{
			_switchState = true;										// AKA ON
			_ignoreSubsequentDown = true;

			AxonSoftwareSwitchEvent *swEvent = new AxonSoftwareSwitchEvent(tmp2->getSwitchNumber());
			swEvent->setSwitchState( true );
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
#ifdef DEBUG_LATCHING_SWITCH_ACTION
			Serial.print( F("AxonLatchingSwitchLogicBlock::event ") );
			Serial.print( F("creating Software Switch Event ") );
			Serial.print( swEvent->getGroupID() ); 
			Serial.println( F(", ON") );
#endif
			executeOnActions( this, swEvent );
			executeChangeActions( this, swEvent );
				
			delete swEvent;

			delete tmp;     // THIS IS NOT A DUPLICATE of the delete lower down... but releases the memory correctly
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
			return;
		}
		
		if ( (_switchState == true) && tmp2->getSwitchState() )			// transission to "down from on"
		{
			_switchState = false;										// AKA OFF
			_ignoreSubsequentDown = true;

			AxonSoftwareSwitchEvent *swEvent = new AxonSoftwareSwitchEvent(tmp2->getSwitchNumber());
			swEvent->setSwitchState( false );
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
#ifdef DEBUG_LATCHING_SWITCH_ACTION
			Serial.print( F("AxonLatchingSwitchLogicBlock::event ") );
			Serial.print( F("creating Software Switch Event ") );
			Serial.print( swEvent->getGroupID() );  
			Serial.println( F(", OFF") );
#endif
			executeOffActions( this, swEvent );
			executeChangeActions( this, swEvent );
			
			delete swEvent;

			delete tmp;     // THIS IS NOT A DUPLICATE of the delete lower down... but releases the memory correctly
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
			return;
		}
		
		_ignoreSubsequentDown = false;									// start looking for "down from off"
	}
	
	delete tmp;
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
}