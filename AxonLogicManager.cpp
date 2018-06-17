#include "AxonLogicManager.h"
#include "AxonStorage.h"

#include "AxonDebugDefines.h"
#include "AxonCheckMem.h"

AxonLogicManager *AxonLogicManager::_instance = 0;

const uint8_t AxonLogicManager::NO_ERROR = 0;
const uint8_t AxonLogicManager::INVALID_LOGIC_NUMBER = 1;
const uint8_t AxonLogicManager::UNABLE_TO_WRITE = 2;

AxonLogicManager *AxonLogicManager::instance()
{
	if (!_instance)
	{
		_instance = new AxonLogicManager();
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
	}
	return _instance;
}

/*
 *  CONSTRUCTOR FOR CLASS
 */
AxonLogicManager::AxonLogicManager()
{
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
#ifdef DEBUG_LISTS
	Serial.println( F("AxonLogicManager::ctor") );
#endif
}

void AxonLogicManager::format()
{
	AxonStorage::instance()->format( _baseAddress, 0x00, (_maxLogicItems * _logicItemSize) );
}

uint8_t AxonLogicManager::defineLogic( uint16_t logicNumber, const uint8_t *logicDefinitionBuffer, uint8_t bufferSize )
{
	if ((logicNumber < 0) or (logicNumber >= _maxLogicItems))
	{
		return (INVALID_LOGIC_NUMBER);
	}	
	
	if (AxonStorage::instance()->write( _baseAddress + (logicNumber * _logicItemSize), logicDefinitionBuffer, bufferSize ) != AxonStorage::NO_ERROR)
	{
		return (UNABLE_TO_WRITE);
	}
}

void AxonLogicManager::__REMOVE__check_written( uint16_t logicNumber )
{
	uint8_t buffer[_logicItemSize+1] = {0};
	
	uint16_t tmpLogicNumber = constrain( logicNumber, 0, _maxLogicItems );
	
	AxonStorage::instance()->read( _baseAddress + (tmpLogicNumber * _logicItemSize), &buffer, _logicItemSize );
	
	Serial.print( "LogicType:" );
	Serial.println( buffer[0], HEX );
	
	for(uint8_t i = 1; i <= _logicItemSize/2; i++)
	{
		Serial.print( "Action");
		Serial.print( i );
		Serial.print( ":" );

		uint16_t tmp = ((buffer[(i*2)-1])<<8) | (buffer[(i*2)]);
		Serial.print( tmp, HEX );
		Serial.println();
	}
}
