/* originally by Simon Peace
 * a wrapper for the genie TouchScreen to provide single access throughtout class model
 * a singleton class
 * VERSION 1.0 10/03/2018
 */

#include "Arduino.h"
#include "AxonTouchScreen.h"
#include "AxonGeneralStorage.h"

#include "AxonDebugDefines.h"

AxonTouchScreen *AxonTouchScreen::_instance = 0;

AxonTouchScreen *AxonTouchScreen::instance()
{
	if (!_instance)
	{
		_instance = new AxonTouchScreen();
	}
	return _instance;
}

/*
 *  CONSTRUCTOR FOR CLASS
 */
AxonTouchScreen::AxonTouchScreen()
{
	_genie = new Genie();
	
	Serial1.begin(200000);        // this is the main screen "Genie" serial path
	_genie->Begin( Serial1 );

	pinMode( _RESET_LINE, OUTPUT );       // RESET the screen.
	digitalWrite( _RESET_LINE, HIGH );
	delay(100);							// should do something about these delays
	digitalWrite( _RESET_LINE, LOW );
	delay(3500);						// should do something about these delays
	
	uint8_t tmp = AxonGeneralStorage::instance()->readTouchScreenContrast();
	setContrast( tmp );
}

void AxonTouchScreen::showTunerScreen()
{
	_genie->WriteObject( GENIE_OBJ_FORM, 0, 0 );  // show tuner form
}

void AxonTouchScreen::showMainScreen()
{
	_genie->WriteObject( GENIE_OBJ_FORM, 1, 0 );  // show main form
}

void AxonTouchScreen::setContrast( uint8_t contrast )
{
	_genie->WriteContrast( (contrast & 0x0F) );				// only use 0..15 values
}

/*






  genie.WriteStr( 7, AxeFX_sceneNumber + 1 );

  genie.WriteStr( 2, AxeFX_presetName );

  genie.WriteStr( 3, AxeFX_presetNumber );

  genie.WriteStr( 7, AxeFX_sceneNumber + 1 );

  genie.WriteStr( 7, AxeFX_sceneNumber + 1 );


  genie.WriteObject( GENIE_OBJ_FORM, 1, 0 );  // show preset form
  genie.WriteStr( 2, AxeFX_presetName );
  genie.WriteStr( 3, AxeFX_presetNumber );
  genie.WriteStr( 7, AxeFX_sceneNumber + 1 );

  genie.WriteObject( GENIE_OBJ_STRINGS, 0, AxeFX_noteNumber );

  genie.WriteObject( GENIE_OBJ_STRINGS, 1, AxeFX_stringNumber - 1);

 
    genie.WriteObject( GENIE_OBJ_GAUGE, 0, AxeFX_pitch );
    if (pitch >= 63)
    {
      genie.WriteObject( GENIE_OBJ_LED, 0, 1 );
    }
    else
    {
      genie.WriteObject( GENIE_OBJ_LED, 0, 0 );
    }
    if (pitch <= 63)
    {
      genie.WriteObject( GENIE_OBJ_LED, 1, 1 );
    }
    else
    {
      genie.WriteObject( GENIE_OBJ_LED, 1, 0 );
    }

*/
 
