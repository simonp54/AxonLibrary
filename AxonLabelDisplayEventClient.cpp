/*
 * AxonLabelDisplayEventClient - an object that watches a switch "Subject"... and executes configured commands for "on" and "off"
 */
#include "AxonLabelDisplayEventClient.h"
#include "AxonSoftwareSwitchEvent.h"
#include "Arduino.h"

#include "AxonDebugDefines.h"
#include "AxonCheckMem.h"



void AxonLabelDisplayEventClient::setOnLabel( const char *label )
{
	snprintf( _onLabel, 6, "%s", label );
	_w = (AxonScribble::instance()->getDisplayWidth()>>1)-(AxonScribble::instance()->getStrWidth(_onLabel)>>1);
}

void AxonLabelDisplayEventClient::setOffLabel( const char *label )
{
	snprintf( _offLabel, 6, "%s", label );
}

AxonLabelDisplayEventClient::AxonLabelDisplayEventClient( uint8_t screenNumber, const char *onLabel, const char *offLabel )
{
	if ((screenNumber >= 0) && (screenNumber <= 23))
	{
		_softwareSwitchEvent = new AxonSoftwareSwitchEvent( screenNumber );
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
		
		AxonEventManager::instance()->clientRegister( this, _softwareSwitchEvent );

		_row = screenNumber >> 3;
		_col = screenNumber - (_row << 3);
		_row++;
		_col++;
	}
	setOnLabel( onLabel );
	setOffLabel( offLabel );
	
	AxonScribble::instance()->selectSingle( _row, _col );
	AxonScribble::instance()->centreText( _offLabel );
}

AxonLabelDisplayEventClient::~AxonLabelDisplayEventClient()
{
	if (_softwareSwitchEvent)
	{
		AxonEventManager::instance()->clientDeregister( this );
	
		delete _softwareSwitchEvent;
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
	}
}

void AxonLabelDisplayEventClient::event( AxonEvent *event )
{
	static u8g2_uint_t h = (AxonScribble::instance()->getDisplayHeight()>>1)+(AxonScribble::instance()->getAscent()>>1);
	static AxonScribble *aScribble = AxonScribble::instance();
	
	
#ifdef DEBUG_LABEL_DISPLAY
	Serial.print( F("AxonLabelDisplayEventClient::event         received:") );
	Serial.println( event->getGroupID() );
#endif
	AxonSoftwareSwitchEvent *tmp = new AxonSoftwareSwitchEvent( 0 );				// switch number irrelevant

	if (event->sameType( tmp ))				// is it a SoftwareSwitchEvent
	{
#ifdef DEBUG_LABEL_DISPLAY
		Serial.print( F("AxonLabelDisplayEventClient::event ") );
		Serial.println( F("is a software switch type") );
#endif		
		AxonSoftwareSwitchEvent *tmp2 = event;											// this is now safe to do!	
	
		if ( tmp2->getSwitchState() )													// switch has notified us it's ON
		{
			// draw ON state rendering
#ifdef DEBUG_LABEL_DISPLAY_REDRAW
			Serial.println( F("Redraw ON") );
#endif
			aScribble->selectSingle( _row, _col );

			aScribble->clearBuffer();          // clear the internal memory
//			aScribble->setFont(u8g_font_helvR24); // choose a suitable font
//			aScribble->setFontPosBaseline();
//			aScribble->setFontRefHeightText();
	
			aScribble->drawStr(_w,h, _onLabel); // write something to the internal memory
			aScribble->drawRFrame( 5, 5, 118, 54, 5 );
			aScribble->drawRFrame( 6, 6, 116, 52, 2 );
			aScribble->sendBuffer();          // transfer internal memory to the display
		}
		else
		{
#ifdef DEBUG_LABEL_DISPLAY_REDRAW
			Serial.println( F("Redraw OFF") );
#endif
			// draw OFF state rendering			
			aScribble->selectSingle( _row, _col );
			aScribble->centreText( _offLabel );
		}
	}
	
	delete tmp;
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
}