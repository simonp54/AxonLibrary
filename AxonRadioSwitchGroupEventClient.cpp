/*
 * AxonRadioSwitchGroupEventClient - an object that watches a switch "Subject"... and executes configured commands for "on" and "off"
 */
#include "AxonRadioSwitchGroupEventClient.h"
#include "AxonSoftwareSwitchEvent.h"
#include "AxonHardwareSwitchEvent.h"
#include "AxonAFXXLPSceneNumberEvent.h"
#include "AxonScribble.h"
#include "Arduino.h"

#include "AxonDebugDefines.h"
#include "AxonCheckMem.h"



AxonRadioSwitchGroupEventClient::AxonRadioSwitchGroupEventClient( uint8_t switchNumber )
{
	_myVirtualSwitchNumber = switchNumber;
}

AxonRadioSwitchGroupEventClient::~AxonRadioSwitchGroupEventClient()
{
	for(uint8_t i = 0; i < _eventCount; i++)
	{
		AxonEventManager::instance()->clientDeregister( this, _eventList[i] );
		delete _eventList[i];
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
	}
	_eventCount = 0;
}

void AxonRadioSwitchGroupEventClient::addSwitch( uint8_t switchNumber )
{
	if ((switchNumber >= 0) && (switchNumber <= 23))
	{
		if (_eventCount < _MAX_EVENTS)
		{
			AxonHardwareSwitchEvent *event = new AxonHardwareSwitchEvent( switchNumber );
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
			
			AxonEventManager::instance()->clientRegister( this, event );
			
			_eventList[_eventCount] = event;
			_eventCount++;
		}
#ifdef DEBUG_RADIO_GROUP_EVENT_CLIENT
		Serial.print( F("AxonRadioSwitchGroupEventClient::addSwitch ") );
		Serial.print( F("attach: ") );
		Serial.print( _eventCount );
		Serial.println( F(" events(aka switch)") );
#endif
	}
#ifdef DEBUG_RADIO_GROUP_EVENT_CLIENT
	Serial.print( F("AxonRadioSwitchGroupEventClient::addSwitch ") );
	Serial.print( F("bad switchNumber: ") );
	Serial.println( switchNumber );
#endif
}

void AxonRadioSwitchGroupEventClient::removeSwitch( uint8_t switchNumber )
{
	bool found = false;
	for( uint8_t i = 0; i < _eventCount; i++ )
	{
		if (found)
		{
			_eventList[i] = _eventList[i+1];
		}
		else if (_eventList[i]->getSwitchNumber() == switchNumber)
		{
			AxonEventManager::instance()->clientDeregister( this, _eventList[i] );
			delete _eventList[i];
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
			
			found = true;
			_eventList[i] = _eventList[i+1];
		}
	}
	if (found)
	{
		_eventCount--;
	}
#ifdef DEBUG_RADIO_GROUP_EVENT_CLIENT
	Serial.print( F("AxonRadioSwitchGroupEventClient::deleteSwitch ") );
	Serial.print( F("attach: ") );
	Serial.print( _eventCount );
	Serial.println( F(" events") );
#endif
}


void AxonRadioSwitchGroupEventClient::event( AxonEvent *event )
{
	static uint8_t lastSwitchNo = 40;
	
#ifdef DEBUG_RADIO_GROUP_EVENT_CLIENT
	Serial.print( F("AxonRadioSwitchGroupEventClient::event         received:") );
	Serial.println( event->getGroupID() );
#endif

	AxonHardwareSwitchEvent *tmp = new AxonHardwareSwitchEvent( 0 );			// switch number doesn't matter for the subsequent check here
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif

	if (event->sameType(tmp))
	{
#ifdef DEBUG_RADIO_GROUP_EVENT_CLIENT
		Serial.print( F("AxonRadioSwitchGroupEventClient::event ") );
		Serial.println( F("is a hardware switch type") );
#endif		
		AxonHardwareSwitchEvent *tmp2 = event;											// this is now safe to do!	
	
		if (lastSwitchNo == tmp2->getSwitchNumber())
		{
			delete tmp;     // THIS IS NOT A DUPLICATE of the delete lower down... but releases the memory correctly
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
			return;			// do nothing for duplicates
		}

		if ( tmp2->getSwitchState() )					// hardware switch has notified us it's ON
		{
#ifdef DEBUG_RADIO_GROUP_EVENT_CLIENT
			Serial.print( F("switch ") );
			Serial.print( tmp2->getSwitchNumber() );
			Serial.println( F(" is ON") );
#endif
			
			for( uint8_t i = 0; i < _eventCount; i++ )
			{
#ifdef DEBUG_RADIO_GROUP_EVENT_CLIENT
				Serial.print( F("switch ") );
				Serial.println( _eventList[i]->getSwitchNumber() );
#endif
				if (_eventList[i]->getSwitchNumber() == lastSwitchNo)
				{
#ifdef DEBUG_RADIO_GROUP_EVENT_CLIENT
					Serial.println( F("not equal to the sending switch event -- sending FALSE SoftwareSwitchEvent1") );
					Serial.print( F("with this number as the switch number=") );
					Serial.println( _eventList[i]->getSwitchNumber() );
#endif

					AxonSoftwareSwitchEvent *SoftwareSwitchEvent1 = new AxonSoftwareSwitchEvent( _eventList[i]->getSwitchNumber() );
					SoftwareSwitchEvent1->setSwitchState( false );
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif

					if (_offAction)
					{
						_offAction->execute( SoftwareSwitchEvent1 );
					}
					
					AxonEventManager::instance()->addToQueue( SoftwareSwitchEvent1 );
				}
				
				if (_eventList[i]->getSwitchNumber() == tmp2->getSwitchNumber())
				{
					_storedIndex = i;
#ifdef DEBUG_RADIO_GROUP_EVENT_CLIENT
					Serial.println( F("    equal to the sending switch event -- sending TRUE SoftwareSwitchEvent2") );
					Serial.print( F("with this number as the switch number=") );
					Serial.println( _eventList[i]->getSwitchNumber() );
#endif
					AxonSoftwareSwitchEvent *SoftwareSwitchEvent2 = new AxonSoftwareSwitchEvent( _eventList[i]->getSwitchNumber() );
					SoftwareSwitchEvent2->setSwitchState( true );
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif

					if (_onAction)
					{
						_onAction->execute( SoftwareSwitchEvent2 );
					}

					AxonEventManager::instance()->addToQueue( SoftwareSwitchEvent2 );

#ifdef DEBUG_RADIO_GROUP_EVENT_CLIENT
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
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif

					if (_onChangeAction)
					{
						_onChangeAction->execute( RGEvent );
					}

					AxonEventManager::instance()->addToQueue( RGEvent );
				}		
			}
			lastSwitchNo = tmp2->getSwitchNumber();

		}
#ifdef DEBUG_RADIO_GROUP_EVENT_CLIENT
		else
		{
			Serial.print( F("switch ") );
			Serial.print( tmp2->getSwitchNumber() );
			Serial.println( F(" is OFF") );
		}
#endif
	}
	
	delete tmp;
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
}