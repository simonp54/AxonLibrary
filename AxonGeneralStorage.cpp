/* originally by Simon Peace
 * an object to provide "general storage" access in a controlled manner
 * VERSION 1.0 11/03/2018
 */
#include "AxonStorage.h"
#include "AxonGeneralStorage.h"

//#define DEBUG_GENERAL_STORAGE
#include "AxonDebugDefines.h"
#include "AxonCheckMem.h"


AxonGeneralStorage *AxonGeneralStorage::_instance = 0;

AxonGeneralStorage *AxonGeneralStorage::instance()
{
	if (!_instance)
	{
		_instance = new AxonGeneralStorage();
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
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

uint16_t AxonGeneralStorage::readAFXXLPPresetNumber()
{
	uint16_t tmp;
	_AS->read( AXEFX_PRESET_NUMBER_ADDR, &tmp );
	return tmp;
}

void AxonGeneralStorage::writeAFXXLPPresetNumber(uint16_t tmp)
{
	_AS->write( AXEFX_PRESET_NUMBER_ADDR, tmp );
}

uint8_t AxonGeneralStorage::readAFXSceneNumber()
{
	uint8_t tmp;
	_AS->read( AXEFX_SCENE_NUMBER_ADDR, &tmp );
	return tmp;
}

void AxonGeneralStorage::writeAFXSceneNumber( uint8_t tmp )
{
	_AS->write( AXEFX_SCENE_NUMBER_ADDR, tmp);
}

const char *AxonGeneralStorage::readAFXXLPPresetName()
{
	char tmp[AXEFX_PRESET_NAME_MAXIMUM_SIZE+1];
	_AS->read( AXEFX_PRESET_NAME_ADDR, &tmp, AXEFX_PRESET_NAME_MAXIMUM_SIZE );
	tmp[AXEFX_PRESET_NAME_MAXIMUM_SIZE] = '\0';
	return tmp;
}

void AxonGeneralStorage::writeAFXXLPPresetName( const char *name )
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