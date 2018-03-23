#include "AxonRadioSwitchAction.h"
#include "AxonHardwareSwitchEvent.h"
#include "AxonSoftwareSwitchEvent.h"
#include "Arduino.h"

#include "AxonDebugDefines.h"
#include "AxonCheckMem.h"


AxonRadioSwitchAction::AxonRadioSwitchAction()
{
#ifdef DEBUG_RADIO_SWITCH_ACTION
	Serial.println( F("AxonRadioSwitchAction::ctor") );
#endif
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
}

AxonRadioSwitchAction::~AxonRadioSwitchAction()
{
#ifdef DEBUG_RADIO_SWITCH_ACTION
	Serial.println( F("AxonRadioSwitchAction::dtor") );
#endif
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
}

void AxonRadioSwitchAction::execute( AxonAction *sender, AxonEvent *event )
{
#ifdef DEBUG_RADIO_SWITCH_ACTION
	Serial.println();
#endif
	if (!processHardwareSwitchEventStyle( sender, event ))
	{
		processSoftwareSwitchEventStyle( sender, event );
	}
}

	
bool AxonRadioSwitchAction::processHardwareSwitchEventStyle( AxonAction *sender, AxonEvent *event )
{
	AxonHardwareSwitchEvent *tmp = new AxonHardwareSwitchEvent( 0 );		// switch number not important for subsequent check

	if (event->sameType(tmp))
	{
#ifdef DEBUG_RADIO_SWITCH_ACTION
		Serial.println( F("AxonRadioSwitchAction::received a hardware switch event") );
#endif		
		AxonHardwareSwitchEvent *tmp2 = event;											// this is now safe to do!	
	
		if ( _switchState == true )				// we are already "on" hardware "OFFs" dont count for this kind of switch
		{
#ifdef DEBUG_RADIO_SWITCH_ACTION
			Serial.println( F("AxonRadioSwitchAction::already ON so doing NOTHING") );
#endif		
			delete tmp;
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
			return true;				// stop any further processing... were done.
		}
	
	
		if ( (_switchState == false) && tmp2->getSwitchState() )
		{
#ifdef DEBUG_RADIO_SWITCH_ACTION
			Serial.println( F("AxonRadioSwitchAction::going from OFF with DOWN indication") );
#endif		
			_switchState = true;

#ifdef DEBUG_RADIO_SWITCH_ACTION
			Serial.println( F("AxonRadioSwitchAction::sending software ON event to both <ON> and <CHANGE> handlers") );
#endif		
			AxonSoftwareSwitchEvent *swOnEvent = new AxonSoftwareSwitchEvent(tmp2->getSwitchNumber());
			swOnEvent->setSwitchState( true );
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
			if (_onAction)
			{
				_onAction->execute( this, swOnEvent );
			}
			
			if (_changeAction)
			{
				_changeAction->execute( this, swOnEvent );
			}

			delete swOnEvent;
		}

		delete tmp;
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
		return true;				// stop any further processing... were done.
	}

	delete tmp;			// not a duplicate...  but embedded return above stops any further processing (which is unnecessary)
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
	return false;
}





bool AxonRadioSwitchAction::processSoftwareSwitchEventStyle( AxonAction *sender, AxonEvent *event )
{
	AxonSoftwareSwitchEvent *tmp = new AxonSoftwareSwitchEvent( 0 );		// switch number not important for subsequent check

	if (event->sameType(tmp))
	{
#ifdef DEBUG_RADIO_SWITCH_ACTION
		Serial.println( F("AxonRadioSwitchAction::received a software switch event") );
#endif		
		AxonSoftwareSwitchEvent *tmp2 = event;											// this is now safe to do!	
	
		if ( (tmp2->getSwitchState() == false) && (_switchState == true))
		{
#ifdef DEBUG_RADIO_SWITCH_ACTION
			Serial.println( F("AxonRadioSwitchAction::going OFF indication") );
#endif		
			_switchState = false;
#ifdef DEBUG_RADIO_SWITCH_ACTION
			Serial.println( F("AxonRadioSwitchAction::sending software OFF to both <OFF> and <CHANGE> handlers") );
#endif		

			AxonSoftwareSwitchEvent *swOffEvent = new AxonSoftwareSwitchEvent(tmp2->getSwitchNumber());
			swOffEvent->setSwitchState( false );
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif

			if (_offAction)
			{
				_offAction->execute( this, swOffEvent );
			}
			
			if (_changeAction)
			{
				_changeAction->execute( this, swOffEvent );
			}

			delete swOffEvent;

			delete tmp;
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
			return true;
		}
	}
	
	delete tmp;
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
	return false;
}