#include "AxonRadioSwitchGroupAction.h"
#include "AxonSoftwareSwitchEvent.h"
#include "AxonHardwareSwitchEvent.h"
#include "AxonAFXXLPSceneNumberEvent.h"
#include "AxonScribble.h"
#include "Arduino.h"

#include "AxonDebugDefines.h"
#include "AxonCheckMem.h"



AxonRadioSwitchGroupAction::AxonRadioSwitchGroupAction( )
{
#ifdef DEBUG_RADIO_SWITCH_GROUP_ACTION
	Serial.println( F("AxonRadioSwitchGroupAction::ctor") );
#endif
}

AxonRadioSwitchGroupAction::~AxonRadioSwitchGroupAction()
{
#ifdef DEBUG_RADIO_SWITCH_GROUP_ACTION
	Serial.println( F("AxonRadioSwitchGroupAction::dtor") );
#endif
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
}

void AxonRadioSwitchGroupAction::addSwitch( AxonAction *action )
{
	if (_switchListCount < _MAX_GROUP_SIZE)
	{		
		_switchList[_switchListCount] = action;
		_switchListCount++;

#ifdef DEBUG_RADIO_SWITCH_GROUP_ACTION
		Serial.print( F("AxonRadioSwitchGroupAction::addSwitch ") );
		Serial.print( F("attach: ") );
		Serial.print( _switchListCount );
		Serial.println( F(" action (aka switch)") );
#endif
	}
#ifdef DEBUG_WARNINGS
	else
	{
		Serial.print( F("AxonRadioSwitchGroupAction::addSwitch ") );
		Serial.print( F("unable to attach: ") );
		Serial.print( _switchListCount );
		Serial.println( F(" action (aka switch)") );
	}
#endif
}

void AxonRadioSwitchGroupAction::removeSwitch( AxonAction *action )
{
	bool found = false;
	for( uint8_t i = 0; i < _switchListCount; i++ )
	{
		if (found)
		{
			_switchList[i] = _switchList[i+1];
		}
		else if (_switchList[i] == action)				// point to the same memory
		{
			found = true;
			_switchList[i] = _switchList[i+1];
			_switchListCount--;
		}
	}
#ifdef DEBUG_RADIO_SWITCH_GROUP_ACTION
	Serial.print( F("AxonRadioSwitchGroupAction::deleteSwitch ") );
	Serial.print( F("attach: ") );
	Serial.print( _switchListCount );
	Serial.println( F(" action (aka switch)") );
#endif
}


void AxonRadioSwitchGroupAction::execute( AxonAction *sender, AxonEvent *event )
{
#ifdef DEBUG_RADIO_SWITCH_ACTION
	Serial.println();
#endif
	if (!processSoftwareSwitchEventStyle( sender, event ) )
	{
		processAFXXLPSceneNumberEventStyle ( sender, event );
	}
}

bool AxonRadioSwitchGroupAction::processSoftwareSwitchEventStyle( AxonAction *sender, AxonEvent *event )
{
	AxonSoftwareSwitchEvent *tmp = new AxonSoftwareSwitchEvent( 0 );			// switch number doesn't matter for the subsequent check here
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif

	if (event->sameType(tmp))
	{
#ifdef DEBUG_RADIO_SWITCH_ACTION
			Serial.println( F("AxonRadioSwitchGroupAction::received software event") );
#endif		
		AxonSoftwareSwitchEvent *tmp2 = event;											// this is now safe to do!	
		// switch off the last known on switch
		if (_lastIndexOn < _switchListCount)			// its set outside (greater than) the range initially
		{
#ifdef DEBUG_RADIO_SWITCH_ACTION
			Serial.println( F("AxonRadioSwitchGroupAction::switching OFF the last <on> switch in the group") );
			Serial.print( F("AxonRadioSwitchGroupAction::_lastIndexOn is (") );
			Serial.print( _lastIndexOn );
			Serial.println( F(")") );
#endif		
			if (_switchList[_lastIndexOn])
			{
#ifdef DEBUG_RADIO_SWITCH_ACTION
				Serial.println( F("AxonRadioSwitchGroupAction::we have a switch to execute on...") );
#endif		
				AxonSoftwareSwitchEvent *swEvent = new AxonSoftwareSwitchEvent( 100 );
				swEvent->setSwitchState( false );
				_switchList[_lastIndexOn]->execute( this, swEvent );
				delete swEvent;
			}
		}
	
		for( uint8_t i = 0; i < _switchListCount; i++ )
		{
			if (_switchList[i] == sender)			// this is the "list match" for the ON switch notification
			{
#ifdef DEBUG_RADIO_SWITCH_ACTION
				Serial.println( F("AxonRadioSwitchGroupAction::found the matching ON switch") );
				Serial.println( F("AxonRadioSwitchGroupAction::but only execute the <CHANGE> handler if different index") );
				Serial.print( F("AxonRadioSwitchGroupAction::index is (") );
				Serial.print( i );
				Serial.println( F(")") );
				Serial.print( F("AxonRadioSwitchGroupAction::_lastIndexOn is (") );
				Serial.print( _lastIndexOn );
				Serial.println( F(")") );
#endif		
				if ( _lastIndexOn != i )
				{
					if ( _changeAction )
					{
#ifdef DEBUG_RADIO_SWITCH_ACTION
						Serial.println( F("AxonRadioSwitchGroupAction::create group message (aka send CC probably!)") );
#endif		
						// so this is a group message which provides an index number output for use in commands maybe later
						// e.g. axefx scene change needs a number of 0 through 7 to set the scene... the index number here
						// is just a number that is "understandable" in the context of the radio group only...
						AxonSoftwareSwitchEvent *RGEvent = new AxonSoftwareSwitchEvent( 100 );
						RGEvent->setVal( i );

#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif

						_changeAction->execute( this, RGEvent );
						delete RGEvent;
					}
				}
				_lastIndexOn = i;
				break;
			}			
		}
		delete tmp;
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
		return true;
	}
	else
	{
		delete tmp;
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
		return false;
	}	
}


bool AxonRadioSwitchGroupAction::processAFXXLPSceneNumberEventStyle( AxonAction *sender, AxonEvent *event )
{
	AxonAFXXLPSceneNumberEvent *tmp = new AxonAFXXLPSceneNumberEvent();			// switch number doesn't matter for the subsequent check here
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif

	if (event->sameType(tmp))
	{
#ifdef DEBUG_RADIO_SWITCH_ACTION
		Serial.println( F("AxonRadioSwitchGroupAction::received Axe FX XL Plus Scene Number event") );
#endif		
		AxonAFXXLPSceneNumberEvent *tmp2 = event;											// this is now safe to do!	
	
		if ( _lastIndexOn == tmp2->getSceneNumber() )
		{
			// already correctly set so do nothing
#ifdef DEBUG_RADIO_SWITCH_ACTION
			Serial.println( F("AxonRadioSwitchGroupAction::doing NOTHING _lastIndexOn is the same as sceneNumber received") );
#endif
			delete tmp;
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
			return true;
		}
	
		if (tmp2->getSceneNumber() < _switchListCount)
		{
#ifdef DEBUG_RADIO_SWITCH_ACTION
			Serial.println( F("AxonRadioSwitchGroupAction::sending hardware DOWN event") );
			Serial.print( F("AxonRadioSwitchGroupAction::to index (") );
			Serial.print( tmp2->getSceneNumber() );
			Serial.println( F(")") );
#endif		
			AxonHardwareSwitchEvent *hwEvent = new AxonHardwareSwitchEvent( 100 );
			hwEvent->setSwitchState( true );
			_switchList[tmp2->getSceneNumber()]->execute( this, hwEvent );
			delete hwEvent;
		}
		
		delete tmp;
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
		return true;
	}
	else
	{
		delete tmp;
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
		return false;
	}
}