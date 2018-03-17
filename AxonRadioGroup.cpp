/*
 * AxonRadioGroup - an object that watches a switch "Subject"... and executes configured commands for "on" and "off"
 */
#include "AxonRadioGroup.h"
#include "AxonSoftwareSwitchEvent.h"
#include "AxonHardwareSwitchEvent.h"
#include "AxonScribble.h"
#include "Arduino.h"

#include "AxonDebugDefines.h"

AxonRadioGroup::AxonRadioGroup( uint8_t switchNumber )
{
	_myVirtualSwitchNumber = switchNumber;
}

void AxonRadioGroup::eventRegister( AxonHardwareSwitchEvent *event )
{
	if (_eventCount < _MAX_EVENTS)
	{
		_eventList[_eventCount] = event;
		_eventCount++;
	}
#ifdef DEBUG_AXON_RADIO_GROUP_EVENT_CLIENT
	Serial.print( F("AxonRadioGroup::eventRegister ") );
	Serial.print( F("attach: ") );
	Serial.print( _eventCount );
	Serial.println( F(" events") );
#endif
}

void AxonRadioGroup::eventDeregister(AxonHardwareSwitchEvent *event)				// find the pointer "match" shuffle the list up and lower the count "if found"
{
	bool found = false;
	for( uint8_t i = 0; i < _eventCount; i++ )
	{
		if (found)
		{
			_eventList[i] = _eventList[i+1];
		}
		else if (_eventList[i] == event)
		{
			found = true;
			_eventList[i] = _eventList[i+1];
		}
	}
	if (found)
	{
		_eventCount--;
	}
#ifdef DEBUG_AXON_RADIO_GROUP_EVENT_CLIENT
	Serial.print( F("AxonRadioGroup::eventDeregister ") );
	Serial.print( F("attach: ") );
	Serial.print( _eventCount );
	Serial.println( F(" observers") );
#endif
}


void AxonRadioGroup::event( AxonEvent *event )
{
	static uint8_t lastSwitchNo = 40;
	
#ifdef DEBUG_AXON_RADIO_GROUP_EVENT_CLIENT
	Serial.print( F("AxonRadioGroup::event         received:") );
	Serial.println( event->getGroupID() );
#endif

	AxonHardwareSwitchEvent *tmp = new AxonHardwareSwitchEvent( 0 );			// switch number doesn't matter for the subsequent check here

	if (event->sameType(tmp))
	{
#ifdef DEBUG_AXON_RADIO_GROUP_EVENT_CLIENT
		Serial.print( F("AxonRadioGroup::event ") );
		Serial.println( F("is a hardware switch type") );
#endif		
		AxonHardwareSwitchEvent *tmp2 = event;											// this is now safe to do!	
	
		if (lastSwitchNo == tmp2->getSwitchNumber())
		{
			delete tmp;     // THIS IS NOT A DUPLICATE of the delete lower down... but releases the memory correctly
			return;			// do nothing for duplicates
		}

		if ( tmp2->getSwitchState() )													// hardware switch has notified us it's ON
		{
#ifdef DEBUG_AXON_RADIO_GROUP_EVENT_CLIENT
			Serial.print( F("switch ") );
			Serial.print( tmp2->getSwitchNumber() );
			Serial.println( F(" is ON") );
#endif
			
			for( uint8_t i = 0; i < _eventCount; i++ )
			{
#ifdef DEBUG_AXON_RADIO_GROUP_EVENT_CLIENT
				Serial.print( F("switch ") );
				Serial.println( _eventList[i]->getSwitchNumber() );
#endif
				if (_eventList[i]->getSwitchNumber() == lastSwitchNo)
				{
#ifdef DEBUG_AXON_RADIO_GROUP_EVENT_CLIENT
					Serial.println( F("not equal to the sending switch event -- sending FALSE SoftwareSwitchEvent1") );
					Serial.print( F("with this number as the switch number=") );
					Serial.println( _eventList[i]->getSwitchNumber() );
#endif

					AxonSoftwareSwitchEvent *SoftwareSwitchEvent1 = new AxonSoftwareSwitchEvent( _eventList[i]->getSwitchNumber() );
					SoftwareSwitchEvent1->setSwitchState( false );

					if (_offAction)
					{
						_offAction->execute( SoftwareSwitchEvent1 );
					}
					
					AxonEventManager::instance()->addToQueue( SoftwareSwitchEvent1 );
				}
				
				if (_eventList[i]->getSwitchNumber() == tmp2->getSwitchNumber())
				{
#ifdef DEBUG_AXON_RADIO_GROUP_EVENT_CLIENT
					Serial.println( F("    equal to the sending switch event -- sending TRUE SoftwareSwitchEvent2") );
					Serial.print( F("with this number as the switch number=") );
					Serial.println( _eventList[i]->getSwitchNumber() );
#endif
					AxonSoftwareSwitchEvent *SoftwareSwitchEvent2 = new AxonSoftwareSwitchEvent( _eventList[i]->getSwitchNumber() );
					SoftwareSwitchEvent2->setSwitchState( true );

					if (_onAction)
					{
						_onAction->execute( SoftwareSwitchEvent2 );
					}

					AxonEventManager::instance()->addToQueue( SoftwareSwitchEvent2 );

#ifdef DEBUG_AXON_RADIO_GROUP_EVENT_CLIENT
					Serial.println( F("sending *radio group* switch message") );
					Serial.print( F("with this number as the switch number=") );
					Serial.println( _myVirtualSwitchNumber );
					Serial.print( F("and this as the value=") );
					Serial.println( i );
#endif
					// so this is a group message which provides an index number output for use in commands maybe later
					// e.g. axefx scene change needs a number of 0 through 7 to set the scene... the index number here
					// is just a number that is "understandable" in the context of the radio group only...
					AxonSoftwareSwitchEvent *RGEvent = new AxonSoftwareSwitchEvent( _myVirtualSwitchNumber );
					RGEvent->setVal( i );

					if (_onChangeAction)
					{
						_onChangeAction->execute( RGEvent );
					}

					AxonEventManager::instance()->addToQueue( RGEvent );
				}		
			}
			lastSwitchNo = tmp2->getSwitchNumber();

		}
#ifdef DEBUG_AXON_RADIO_GROUP_EVENT_CLIENT
		else
		{
			Serial.print( F("switch ") );
			Serial.print( tmp2->getSwitchNumber() );
			Serial.println( F(" is OFF") );
		}
#endif
	}
	
	delete tmp;
}