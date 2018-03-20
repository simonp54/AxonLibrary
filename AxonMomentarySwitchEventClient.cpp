/*
 * AxonMomentarySwitchEventClient - an object that watches a switch "Subject"... and executes configured commands for "on" and "off"
 */
#include "AxonMomentarySwitchEventClient.h"
#include "AxonHardwareSwitchEvent.h"
#include "AxonSoftwareSwitchEvent.h"
#include "Arduino.h"

#include "AxonDebugDefines.h"
#include "AxonCheckMem.h"


AxonMomentarySwitchEventClient::AxonMomentarySwitchEventClient( uint8_t hardwareSwitchNumber )
{
	if ((hardwareSwitchNumber>=0)  && (hardwareSwitchNumber<=23))
	{
		_hardwareSwitchEvent = new AxonHardwareSwitchEvent( hardwareSwitchNumber );
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
		
		AxonEventManager::instance()->clientRegister( this, _hardwareSwitchEvent );
	}
}

AxonMomentarySwitchEventClient::~AxonMomentarySwitchEventClient()
{
	if (_hardwareSwitchEvent)
	{
		AxonEventManager::instance()->clientDeregister( this );

		delete _hardwareSwitchEvent;
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
	}
}

void AxonMomentarySwitchEventClient::setInterval( uint16_t interval )
{
	_interval = interval;
}

uint16_t AxonMomentarySwitchEventClient::getInterval()
{
	return _interval;
}

void AxonMomentarySwitchEventClient::event( AxonEvent *event )
{
#ifdef DEBUG_MOMENTARY
	Serial.print( F("AxonMomentarySwitchEventClient::event         received:") );
	Serial.println( event->getGroupID() );
#endif
	AxonHardwareSwitchEvent *tmp = new AxonHardwareSwitchEvent( 0 );		// switch number not important for subsequent check

	if (event->sameType(tmp))
	{
#ifdef DEBUG_MOMENTARY
		Serial.print( F("AxonMomentarySwitchEventClient::event ") );
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
#ifdef DEBUG_MOMENTARY
				Serial.print( F("AxonMomentarySwitchEventClient::event ") );
				Serial.print( F("creating Software Switch Event ") );
#endif
#ifdef DEBUG_MOMENTARY_JUST_ONOFFS
				Serial.print( swEvent->getSwitchNumber() ); 
				Serial.println( F(", ON") );
#endif
				if (_onAction)
				{
					_onAction->execute( swEvent );
				}

				AxonEventManager::instance()->addToQueue( swEvent );
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
#ifdef DEBUG_MOMENTARY
				Serial.print( F("AxonMomentarySwitchEventClient::event ") );
				Serial.print( F("creating Software Switch Event ") );
#endif
#ifdef DEBUG_MOMENTARY_JUST_ONOFFS
				Serial.print( swEvent->getSwitchNumber() );
				Serial.println( F(", OFF") );
#endif
				if (_offAction)
				{
					_offAction->execute( swEvent );
				}

				AxonEventManager::instance()->addToQueue( swEvent );
			}
			delete tmp;     // THIS IS NOT A DUPLICATE of the delete lower down... but releases the memory correctly
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
			return;
		}
#ifdef DEBUG_MOMENTARY
		else
		{
			Serial.print( F("AxonMomentarySwitchEventClient::event ") );
			Serial.println( F("is NOT a hardware switch type") );
		}
#endif
	}
	
	delete tmp;
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
}