/*
 * AxonMomentarySwitchAction - an object that watches a switch "Subject"... and executes configured commands for "on" and "off"
 */
#include "AxonMomentarySwitchAction.h"
#include "AxonHardwareSwitchEvent.h"
#include "AxonSoftwareSwitchEvent.h"
#include "Arduino.h"

#include "AxonDebugDefines.h"
#include "AxonCheckMem.h"


AxonMomentarySwitchAction::AxonMomentarySwitchAction()
{
#ifdef DEBUG_MOMENTARY_SWITCH_ACTION
	Serial.println( F("AxonMomentarySwitchAction::ctor") );
#endif
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
}

AxonMomentarySwitchAction::~AxonMomentarySwitchAction()
{
#ifdef DEBUG_MOMENTARY_SWITCH_ACTION
	Serial.println( F("AxonMomentarySwitchAction::dtor") );
#endif
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
}

void AxonMomentarySwitchAction::setInterval( uint16_t interval )
{
	_interval = interval;
}

uint16_t AxonMomentarySwitchAction::getInterval()
{
	return _interval;
}

void AxonMomentarySwitchAction::execute( AxonAction *sender, AxonEvent *event )
{
#ifdef DEBUG_MOMENTARY_SWITCH_ACTION
	Serial.print( F("AxonMomentarySwitchAction::event         received:") );
	Serial.println( event->getGroupID() );
#endif
	AxonHardwareSwitchEvent *tmp = new AxonHardwareSwitchEvent( 0 );		// switch number not important for subsequent check

	if (event->sameType(tmp))
	{
#ifdef DEBUG_MOMENTARY_SWITCH_ACTION
		Serial.print( F("AxonMomentarySwitchAction::event ") );
		Serial.println( F("is a hardware switch type") );
#endif		
		AxonHardwareSwitchEvent *tmp2 = event;											// this is now safe to do!	
	
		if ( (_switchState == false) && tmp2->getSwitchState() )							// transission to "down from off"
		{
			_switchState = true;
			_startMillis = millis();
		}

		if ( (_switchState == true) && tmp2->getSwitchState() )							// switch "held down"
		{
			if ( ( _startMillis > 0 ) && ( _startMillis + _interval <= millis() ) )		// is it long enough?
			{
				_startMillis = 0;														// stop our timer
								
				AxonSoftwareSwitchEvent *swEvent = new AxonSoftwareSwitchEvent(tmp2->getSwitchNumber());
				swEvent->setSwitchState( true );
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
#ifdef DEBUG_MOMENTARY_SWITCH_ACTION
				Serial.print( F("AxonMomentarySwitchAction::event ") );
				Serial.print( F("creating Software Switch Event ") );
#endif
#ifdef DEBUG_MOMENTARY_SWITCH_ACTION
				Serial.print( swEvent->getSwitchNumber() ); 
				Serial.println( F(", ON") );
#endif
				if (_onAction)
				{
					_onAction->execute( this, swEvent );
				}
				
				if (_changeAction)
				{
					_changeAction->execute( this, swEvent );
				}
				delete swEvent;
				
			}
			delete tmp;     // THIS IS NOT A DUPLICATE of the delete lower down... but releases the memory correctly
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
			return;
		}

		if ( (_switchState == true) && !tmp2->getSwitchState() )							// transission to "up from on"
		{
			_switchState = false;
			if (_startMillis == 0)														// the timer expired (it would be greater than 0 if still running
			{																			// and its impossible to get here unless it was started
				AxonSoftwareSwitchEvent *swEvent = new AxonSoftwareSwitchEvent(tmp2->getSwitchNumber());
				swEvent->setSwitchState( false );
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
#ifdef DEBUG_MOMENTARY_SWITCH_ACTION
				Serial.print( F("AxonMomentarySwitchAction::event ") );
				Serial.print( F("creating Software Switch Event ") );
#endif
#ifdef DEBUG_MOMENTARY_SWITCH_ACTION
				Serial.print( swEvent->getSwitchNumber() );
				Serial.println( F(", OFF") );
#endif
				if (_offAction)
				{
					_offAction->execute( this, swEvent );
				}
				
				if (_changeAction)
				{
					_changeAction->execute( this, swEvent );
				}
				delete swEvent;
				
			}
			delete tmp;     // THIS IS NOT A DUPLICATE of the delete lower down... but releases the memory correctly
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
			return;
		}
#ifdef DEBUG_MOMENTARY_SWITCH_ACTION
		else
		{
			Serial.print( F("AxonMomentarySwitchAction::event ") );
			Serial.println( F("is NOT a hardware switch type") );
		}
#endif
	}
	
	delete tmp;
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
}