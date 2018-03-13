/*
 * AxonLatchingSwitch - an object that watches a switch "Subject"... and executes configured commands for "on" and "off"
 */
#include "AxonLatchingSwitch.h"
#include "AxonHardwareSwitchEvent.h"
#include "AxonSoftwareSwitchEvent.h"
#include "Arduino.h"

#include "AxonDebugDefines.h"


void AxonLatchingSwitch::event( AxonEvent *event )
{
#ifdef DEBUG_AXON_LATCHING
	Serial.print( F("AxonLatchingSwitch::event ") );
	Serial.println( event->getGroupID() );
#endif
	AxonHardwareSwitchEvent *tmp = new AxonHardwareSwitchEvent( 0 );  // switchnumber irrelevant

	if (event->sameType(tmp))
	{
#ifdef DEBUG_AXON_LATCHING
		Serial.print( F("AxonLatchingSwitch::event ") );
		Serial.println( F("event is a hardware switch type") );
#endif		
		AxonHardwareSwitchEvent *tmp2 = event;	// effectively a type cast to gain access to specific features of this object type
		
#ifdef DEBUG_AXON_LATCHING
		Serial.print( F("AxonLatchingSwitch::event ") );
		Serial.println( tmp2->getSwitchState() );
#endif		
	
		if ( (_ignoreSubsequentDown == true) && tmp2->getSwitchState() )
		{
			delete tmp;     // THIS IS NOT A DUPLICATE of the delete lower down... but releases the memory correctly
			return;														// quickly ignore the "duplicated down notifications"
																		// these are for more complex switch types
		}

		if ( (_switchState == false) && tmp2->getSwitchState() )			// transission to "down from off"
		{
			_switchState = true;										// AKA ON
			_ignoreSubsequentDown = true;

			AxonSoftwareSwitchEvent *swEvent = new AxonSoftwareSwitchEvent(tmp2->getSwitchNumber());
			swEvent->setSwitchState( true );
#ifdef DEBUG_AXON_LATCHING
			Serial.print( F("AxonLatchingSwitch::event ") );
			Serial.print( F("creating Software Switch Event ") );
			Serial.print( swEvent->getGroupID() ); 
			Serial.println( F(", ON") );
#endif
			AxonEventManager::instance()->addToQueue( swEvent );

			delete tmp;     // THIS IS NOT A DUPLICATE of the delete lower down... but releases the memory correctly
			return;
		}
		
		if ( (_switchState == true) && tmp2->getSwitchState() )			// transission to "down from on"
		{
			_switchState = false;										// AKA OFF
			_ignoreSubsequentDown = true;

			AxonSoftwareSwitchEvent *swEvent = new AxonSoftwareSwitchEvent(tmp2->getSwitchNumber());
			swEvent->setSwitchState( false );
#ifdef DEBUG_AXON_LATCHING
			Serial.print( F("AxonLatchingSwitch::event ") );
			Serial.print( F("creating Software Switch Event ") );
			Serial.print( swEvent->getGroupID() );  
			Serial.println( F(", OFF") );
#endif
			AxonEventManager::instance()->addToQueue( swEvent );

			delete tmp;     // THIS IS NOT A DUPLICATE of the delete lower down... but releases the memory correctly
			return;
		}
		
		_ignoreSubsequentDown = false;									// start looking for "down from off"
	}
	
	delete tmp;
}