#include "AxonEventClient.h"
#include "AxonEvent.h"
#include "Arduino.h"

void AxonEventClient::event( AxonEvent *event )
{
	Serial.print( F("AxonEventClient::event ") );
	Serial.println( event->getGroupID() );
}


void AxonEventClient::setOnAction( AxonAction *action )
{
	_onAction = action;
}

void AxonEventClient::setOffAction( AxonAction *action )
{
	_offAction = action;
}

void AxonEventClient::setOnChangeAction( AxonAction *action )
{
	_onChangeAction = action;
}