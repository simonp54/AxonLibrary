#include "AxonPresetManager.h"
#include "AxonStorage.h"
#include "AxonSurfaceManager.h"
#include "AxonActionManager.h"

#include "AxonDebugDefines.h"
#include "AxonCheckMem.h"

AxonPresetManager *AxonPresetManager::_instance = 0;

const uint8_t AxonPresetManager::NO_ERROR = 0;
const uint8_t AxonPresetManager::INVALID_PRESET_NUMBER = 1;
const uint8_t AxonPresetManager::UNABLE_TO_WRITE = 2;
const uint8_t AxonPresetManager::UNABLE_TO_READ = 3;

AxonPresetManager *AxonPresetManager::instance()
{
	if (!_instance)
	{
		_instance = new AxonPresetManager();
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
	}
	return _instance;
}

/*
 *  CONSTRUCTOR FOR CLASS
 */
AxonPresetManager::AxonPresetManager()
{
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
#ifdef DEBUG_LISTS
	Serial.println( F("AxonPresetManager::ctor") );
#endif
}

void AxonPresetManager::processOutstanding()
{
	if (_presetQueued)
	{
		_presetQueued = false;
		loadPreset( _qPresetNumber );
	}
}

void AxonPresetManager::format()
{
	AxonStorage::instance()->format( _baseAddress, 0x00, (maxPresetItems * sizeof(AxonPresetInfo_t)) );
}

uint8_t AxonPresetManager::definePreset( uint16_t presetNumber, const AxonPresetInfo_t *presetInfo )
{
	if ((presetNumber < 0) or (presetNumber >= maxPresetItems))
	{
		return( INVALID_PRESET_NUMBER );
	}	
	
	if (AxonStorage::instance()->write( _baseAddress + (presetNumber * sizeof(AxonPresetInfo_t)), presetInfo, sizeof(AxonPresetInfo_t) ))
	{
		return( NO_ERROR );
	}
	return( UNABLE_TO_WRITE );
}

uint8_t AxonPresetManager::getPresetBuffer( uint16_t presetNumber, AxonPresetInfo_t *presetInfo )
{
	if ((presetNumber < 0) or (presetNumber >= maxPresetItems))
	{
		return( INVALID_PRESET_NUMBER );
	}	
	
	if (AxonStorage::instance()->read( _baseAddress + (presetNumber * sizeof(AxonPresetInfo_t)), presetInfo, sizeof(AxonPresetInfo_t) ))
	{
		return( NO_ERROR );
	}
	return( UNABLE_TO_READ );
}

void AxonPresetManager::qPreset( uint16_t presetNumber )
{
	_qPresetNumber = presetNumber;
	_presetQueued = true;
}

void AxonPresetManager::loadPreset( uint16_t presetNumber )
{
	AxonPresetInfo_t presetInfo;
	
	if (getPresetBuffer( presetNumber, &presetInfo ) == NO_ERROR )
	{
		for (uint8_t i = 0; i < actionSlotsPerPreset; i++)
		{
			AxonActionManager::instance()->executeAction( presetInfo.actionSlot[i], NULL );
		}
		
		// add override code here
		
		// for each override action definition in the preset, update the action manager with override action definition
		// using the switch and action number, "overwrite" the action with the overridden action number

		AxonSurfaceManager::instance()->qSurface( presetInfo.surfaceNumber );
	}
}


void AxonPresetManager::__REMOVE__check_written( uint16_t presetNumber )
{
	AxonPresetInfo_t presetInfo;
		
	if (getPresetBuffer( presetNumber, &presetInfo ) == NO_ERROR)
	{
		
		Serial.print( "PRESET DEFINITION:");
		Serial.println( presetNumber );

		Serial.print( "surfaceNumber:");
		Serial.println( presetInfo.surfaceNumber );
		
		for (uint8_t i = 0; i < AxonPresetManager::actionSlotsPerPreset; i++)
		{
			Serial.print( "actionSlot[");
			Serial.print(i);
			Serial.print( "]=" );
			Serial.println( presetInfo.actionSlot[i] );
		}
	}
	else
	{
		Serial.println( "ERROR whilst reading PresetBuffer" );
	}
}
