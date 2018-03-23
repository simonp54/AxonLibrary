/*
 * AxonActionEventClient - an object that watches a switch "Subject"... and executes configured Actions for "on" and "off"
 */
#include "AxonActionEventClient.h"
#include "AxonSwitchEvent.h"
#include "Arduino.h"

#include "AxonDebugDefines.h"
#include "AxonCheckMem.h"



void AxonActionEventClient::setOnAction( AxonAction *action )
{
	_onAction = action;
}

void AxonActionEventClient::setOffAction( AxonAction *action )
{
	_offAction = action;
}

void AxonActionEventClient::setOnChangeAction( AxonAction *action )
{
	_onChangeAction = action;
}

void AxonActionEventClient::event( AxonAction *sender, AxonEvent *event )
{
#ifdef DEBUG_ACTION_EVENT_CLIENT
	Serial.print( F("AxonActionEventClient::event         received:") );
	Serial.println( event->getGroupID() );
#endif
	AxonSwitchEvent *tmp = new AxonSwitchEvent( 0 );		// switch number not important for subsequent check
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif

	if (event->sameType(tmp))
	{
#ifdef DEBUG_ACTION_EVENT_CLIENT
		Serial.print( F("AxonActionEventClient::event ") );
		Serial.println( F("is a switch type") );
#endif		
		AxonSwitchEvent *tmp2 = event;											// this is now safe to do!	
	
		if ( tmp2->getSwitchState() )
		{
			if (_onAction)
			{
#ifdef DEBUG_ACTION_EVENT_CLIENT
		Serial.print( F("AxonActionEventClient::event " ));
		Serial.println( F("execute ON Action") );
		Serial.print( F("with switch value=") );
		Serial.println( tmp2->getVal() );
#endif		
				_onAction->execute( NULL, tmp2);
			}
#ifdef DEBUG_ACTION_EVENT_CLIENT
			else
			{
				Serial.print( F("AxonActionEventClient::event " ) );
				Serial.println( F("no ON Action associated to execute.") );		
			}
#endif		
		}
		else
		{
			if (_offAction)
			{
#ifdef DEBUG_ACTION_EVENT_CLIENT
		Serial.print( F("AxonActionEventClient::event ") );
		Serial.println( F("execute OFF Action") );
		Serial.print( F("with switch value=") );
		Serial.println( tmp2->getVal() );
#endif
				_offAction->execute( NULL, tmp2);
			}
#ifdef DEBUG_ACTION_EVENT_CLIENT
			else
			{
				Serial.print( F("AxonActionEventClient::event ") );
				Serial.println( F("no OFF Action associated to execute.") );		
			}
#endif		
		}
		if (_onChangeAction)
		{
#ifdef DEBUG_ACTION_EVENT_CLIENT
			Serial.print( F("AxonActionEventClient::event ") );
			Serial.println( F("execute CHANGE Action") );
			Serial.print( F("with switch value=") );
			Serial.println( tmp2->getVal() );
#endif
			_onChangeAction->execute( NULL, tmp2);
		}
#ifdef DEBUG_ACTION_EVENT_CLIENT
		else
		{
			Serial.print( F("AxonActionEventClient::event ") );
			Serial.println( F("no CHANGE Action associated to execute.") );		
		}
#endif		
	}
#ifdef DEBUG_ACTION_EVENT_CLIENT
	else
	{
		Serial.print( F("AxonActionEventClient::event ") );
		Serial.println( F("is NOT a switch type") );
	}
#endif
	
	delete tmp;
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
}