#include "AxonEventClient.h"
#include "AxonEvent.h"
#include "Arduino.h"

void AxonEventClient::event( AxonEvent *event )
{
	Serial.print( F("AxonEventClient::event ") );
	Serial.println( event->getGroupID() );
}