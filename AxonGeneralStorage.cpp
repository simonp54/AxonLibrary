/* originally by Simon Peace
 * an object to provide "general storage" access in a controlled manner
 * VERSION 1.0 11/03/2018
 */
#include "AxonStorage.h"
#include "AxonGeneralStorage.h"

//#define DEBUG_GENERAL_STORAGE

AxonGeneralStorage *AxonGeneralStorage::_instance = 0;

AxonGeneralStorage *AxonGeneralStorage::instance()
{
	if (!_instance)
	{
		_instance = new AxonGeneralStorage();
	}
	return _instance;
}

/*
 *  CONSTRUCTOR FOR CLASS
 */
AxonGeneralStorage::AxonGeneralStorage()
{
	_AS = AxonStorage::instance();
}

uint16_t AxonGeneralStorage::readAxeFXPresetNumber()
{
	uint16_t tmp;
	_AS->read( AXEFX_PRESET_NUMBER_ADDR, &tmp );
	return tmp;
}

void AxonGeneralStorage::writeAxeFXPresetNumber(uint16_t tmp)
{
	_AS->write( AXEFX_PRESET_NUMBER_ADDR, tmp );
}

uint8_t AxonGeneralStorage::readAxeFXSceneNumber()
{
	uint16_t tmp;
	_AS->read( AXEFX_SCENE_NUMBER_ADDR, &tmp );
	return tmp;
}

void AxonGeneralStorage::writeAxeFXSceneNumber( uint8_t tmp )
{
	_AS->write( AXEFX_SCENE_NUMBER_ADDR, tmp);
}

const char *AxonGeneralStorage::readAxeFXPresetName()
{
	char tmp[AXEFX_PRESET_NAME_MAXIMUM_SIZE+1];
	_AS->read( AXEFX_PRESET_NAME_ADDR, &tmp, AXEFX_PRESET_NAME_MAXIMUM_SIZE );
	tmp[AXEFX_PRESET_NAME_MAXIMUM_SIZE] = '\0';
	return tmp;
}

void AxonGeneralStorage::writeAxeFXPresetName( const char *name )
{
	_AS->write( AXEFX_PRESET_NAME_ADDR, name, AXEFX_PRESET_NAME_MAXIMUM_SIZE );
}


uint8_t AxonGeneralStorage::readTouchScreenContrast()
{
	uint8_t tmp;
	_AS->read( TOUCH_SCREEN_CONTRAST_ADDR, &tmp );
	return tmp;
}

void AxonGeneralStorage::writeTouchScreenContrast(uint8_t tmp)
{
	_AS->write( TOUCH_SCREEN_CONTRAST_ADDR, tmp );
}