/* originally by Simon Peace
 * a wrapper for the genie TouchScreen to provide single access throughtout class model
 * a singleton class
 * VERSION 1.0 10/03/2018
 */

#include "AxonTouchScreen.h"
#include "AxonGeneralStorage.h"

#include "AxonDebugDefines.h"
#include "AxonCheckMem.h"


AxonTouchScreen *AxonTouchScreen::_instance = 0;

AxonTouchScreen *AxonTouchScreen::instance()
{
	if (!_instance)
	{
		_instance = new AxonTouchScreen();
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
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
}

void AxonTouchScreen::initialise()
{
	contrastSet();
}

void AxonTouchScreen::showTunerScreen()
{
	_genie->WriteObject( GENIE_OBJ_FORM, 0, 0 );  // show tuner form
}

void AxonTouchScreen::showMainScreen()
{
	_genie->WriteObject( GENIE_OBJ_FORM, 1, 0 );  // show main form
	
	showAFXXLPPresetNumber();
	showAFXSceneNumber();
	showAFXXLPPresetName();
}

void AxonTouchScreen::contrastUp()
{
	_genie->WriteContrast( _contrast.up() );				// only use 0..15 values
}

void AxonTouchScreen::contrastDown()
{
	_genie->WriteContrast( _contrast.down() );				// only use 0..15 values
}

void AxonTouchScreen::contrastSet()
{
	_genie->WriteContrast( _contrast.get() );
}

void AxonTouchScreen::setTunerNote( uint8_t note )
{
  static uint8_t noteNumber = 0xFF;

  if (note != noteNumber)
  {
    noteNumber = note;
	
    _genie->WriteObject( GENIE_OBJ_STRINGS, 0, noteNumber );
  }
}

void AxonTouchScreen::setTunerString( uint8_t stringNumber )
{
  static uint8_t stringNo = 0xFF;
  
  if (stringNumber != stringNo)
  {
    stringNo = stringNumber;

	_genie->WriteObject( GENIE_OBJ_STRINGS, 1, stringNo);
  }  
}

void AxonTouchScreen::setTunerData( uint8_t tunerData )
{
	static uint8_t pitch = 0xFF;
  
	if (tunerData != pitch)
	{
		pitch = tunerData;

		_genie->WriteObject( GENIE_OBJ_GAUGE, 0, pitch );

		if (pitch >= 62)
		{
			_genie->WriteObject( GENIE_OBJ_LED, 0, 1 );
		}
		else
		{
			_genie->WriteObject( GENIE_OBJ_LED, 0, 0 );
		}
		if (pitch <= 64)
		{
			_genie->WriteObject( GENIE_OBJ_LED, 1, 1 );
		}
		else
		{
			_genie->WriteObject( GENIE_OBJ_LED, 1, 0 );
		}
	}
}

void AxonTouchScreen::showAFXXLPPresetNumber()
{
	_genie->WriteStr( 3, AxonGeneralStorage::instance()->readAFXXLPPresetNumber() );
}

void AxonTouchScreen::showAFXSceneNumber()
{
	_genie->WriteStr( 7, AxonGeneralStorage::instance()->readAFXSceneNumber() + 1 );
}

void AxonTouchScreen::showAFXXLPPresetName()
{
	_genie->WriteStr( 2, AxonGeneralStorage::instance()->readAFXXLPPresetName() );
}