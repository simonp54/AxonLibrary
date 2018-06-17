#include "AxonActionManager.h"
#include "AxonStorage.h"

#include "AxonDebugDefines.h"
#include "AxonCheckMem.h"

AxonActionManager *AxonActionManager::_instance = 0;

const uint8_t AxonActionManager::NO_ERROR = 0;
const uint8_t AxonActionManager::INVALID_ACTION_NUMBER = 1;
const uint8_t AxonActionManager::UNABLE_TO_WRITE = 2;

AxonActionManager *AxonActionManager::instance()
{
	if (!_instance)
	{
		_instance = new AxonActionManager();
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
	}
	return _instance;
}

/*
 *  CONSTRUCTOR FOR CLASS
 */
AxonActionManager::AxonActionManager()
{
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
#ifdef DEBUG_LISTS
	Serial.println( F("AxonActionManager::ctor") );
#endif
}

void AxonActionManager::format()
{
	AxonStorage::instance()->format( _baseAddress, 0x00, (_maxActionItems * _actionItemSize) );
}

uint8_t AxonActionManager::defineAction( uint16_t actionNumber, const uint8_t *actionDefinitionBuffer, uint8_t bufferSize )
{
	if ((actionNumber < 0) or (actionNumber >= 1024))
	{
		return (INVALID_ACTION_NUMBER);
	}	
	
	if (AxonStorage::instance()->write( _baseAddress + (actionNumber * _actionItemSize), actionDefinitionBuffer, bufferSize ) != AxonStorage::NO_ERROR)
	{
		return (UNABLE_TO_WRITE);
	}
}


void AxonActionManager::executeAction( uint16_t actionNumber )
{
	// check if an instance of this actionNumber exists
	// if it doesn't then create
	// execute the action
}


void AxonActionManager::__REMOVE__check_written( uint16_t actionNumber )
{
	uint8_t buffer[_actionItemSize+1] = {0};
	
	uint16_t tmpActionNumber = constrain( actionNumber, 0, _maxActionItems );
	
	AxonStorage::instance()->read( _baseAddress + (actionNumber * _actionItemSize), &buffer, _actionItemSize );
	
	Serial.print( "ActionType:");
	Serial.println( buffer[0] );
	
	Serial.print( "Param1:");
	Serial.println( buffer[1] );

	Serial.print( "Param2:");
	Serial.println( buffer[2] );

	Serial.print( "Param3:");
	Serial.println( buffer[3] );

	Serial.print( "Param4:");
	Serial.println( buffer[4] );

	Serial.print( "Name:");
	for(uint8_t i = 5; i < _actionItemSize; i++)
	{
		Serial.print( char(buffer[i]) );
	}
	Serial.println();
}
