/*
 * AxonActionClient - an object that watches a switch "Subject"... and executes configured Actions for "on" and "off"
 */
#include "AxonActionClient.h"
#include "AxonSwitchEvent.h"
#include "Arduino.h"

#include "AxonDebugDefines.h"

void AxonActionClient::setOnAction( AxonAction *action )
{
	_onAction = action;
}

void AxonActionClient::setOffAction( AxonAction *action )
{
	_offAction = action;
}

void AxonActionClient::setOnChangeAction( AxonAction *action )
{
	_onChangeAction = action;
}

void AxonActionClient::event( AxonEvent *event )
{
#ifdef DEBUG_AXON_ACTION_CLIENT
	Serial.print( F("AxonActionClient::event         received:") );
	Serial.println( event->getGroupID() );
#endif
	AxonSwitchEvent *tmp = new AxonSwitchEvent( 0 );		// switch number not important for subsequent check

	if (event->sameType(tmp))
	{
#ifdef DEBUG_AXON_ACTION_CLIENT
		Serial.print( F("AxonActionClient::event ") );
		Serial.println( F("is a switch type") );
#endif		
		AxonSwitchEvent *tmp2 = event;											// this is now safe to do!	
	
		if ( tmp2->getSwitchState() )
		{
			if (_onAction)
			{
#ifdef DEBUG_AXON_ACTION_CLIENT
		Serial.print( F("AxonActionClient::event " ));
		Serial.println( F("execute ON Action") );
		Serial.print( F("with switch value=") );
		Serial.println( tmp2->getVal() );
#endif		
				_onAction->execute(tmp2);
			}
#ifdef DEBUG_AXON_ACTION_CLIENT
			else
			{
				Serial.print( F("AxonActionClient::event " ) );
				Serial.println( F("no ON Action associated to execute.") );		
			}
#endif		
		}
		else
		{
			if (_offAction)
			{
#ifdef DEBUG_AXON_ACTION_CLIENT
		Serial.print( F("AxonActionClient::event ") );
		Serial.println( F("execute OFF Action") );
		Serial.print( F("with switch value=") );
		Serial.println( tmp2->getVal() );
#endif
				_offAction->execute(tmp2);
			}
#ifdef DEBUG_AXON_ACTION_CLIENT
			else
			{
				Serial.print( F("AxonActionClient::event ") );
				Serial.println( F("no OFF Action associated to execute.") );		
			}
#endif		
		}
		if (_onChangeAction)
		{
#ifdef DEBUG_AXON_ACTION_CLIENT
			Serial.print( F("AxonActionClient::event ") );
			Serial.println( F("execute CHANGE Action") );
			Serial.print( F("with switch value=") );
			Serial.println( tmp2->getVal() );
#endif
			_onChangeAction->execute(tmp2);
		}
#ifdef DEBUG_AXON_ACTION_CLIENT
		else
		{
			Serial.print( F("AxonActionClient::event ") );
			Serial.println( F("no CHANGE Action associated to execute.") );		
		}
#endif		
	}
#ifdef DEBUG_AXON_ACTION_CLIENT
	else
	{
		Serial.print( F("AxonActionClient::event ") );
		Serial.println( F("is NOT a switch type") );
	}
#endif
	
	delete tmp;
}