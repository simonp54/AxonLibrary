#include "AxonLogicManager.h"
#include "AxonStorage.h"

#include "AxonLatchingSwitchLogicBlock.h"
#include "AxonMomentarySwitchLogicBlock.h"
#include "AxonVariableSwitchLogicBlock.h"

#include "AxonDebugDefines.h"
#include "AxonCheckMem.h"

AxonLogicManager *AxonLogicManager::_instance = 0;

const uint8_t AxonLogicManager::NO_ERROR = 0;
const uint8_t AxonLogicManager::INVALID_LOGIC_NUMBER = 1;
const uint8_t AxonLogicManager::UNABLE_TO_WRITE = 2;
const uint8_t AxonLogicManager::UNABLE_TO_READ = 3;

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
	AxonStorage::instance()->format( _baseAddress, 0x00, _maxLogicItems * sizeof(AxonLogicInfo_t) );
}

uint8_t AxonLogicManager::defineLogic( uint16_t logicNumber, const AxonLogicInfo_t *logicInfo )
{
	if ((logicNumber < 1) or (logicNumber > _maxLogicItems))
	{
		return (INVALID_LOGIC_NUMBER);
	}	
	
	if (AxonStorage::instance()->write( _baseAddress + ((logicNumber-1) * sizeof(AxonLogicInfo_t)), logicInfo, sizeof( AxonLogicInfo_t ) ) )
	{
		return( NO_ERROR );
	}
	return (UNABLE_TO_WRITE);
}

uint8_t AxonLogicManager::getLogicBuffer( uint16_t logicNumber, AxonLogicInfo_t *logicInfo )
{
	if ((logicNumber < 1) or (logicNumber > _maxLogicItems))
	{
		return( INVALID_LOGIC_NUMBER );
	}	
	
	if (AxonStorage::instance()->read( _baseAddress + ((logicNumber-1) * sizeof(AxonLogicInfo_t)), logicInfo, sizeof( AxonLogicInfo_t ) ) )
	{
		return( NO_ERROR );
	}
	return( UNABLE_TO_READ );
}


AxonLogicBlock *AxonLogicManager::createLogic( uint16_t logicNumber )
{
	AxonLogicInfo_t logicInfo;
	AxonLogicBlock *axonLogicBlock = NULL;
	
	if (getLogicBuffer( logicNumber, &logicInfo ) == NO_ERROR)
	{
		switch (logicInfo.logicCode)
		{
			case AxonMomentarySwitchLogicBlock_t:
				axonLogicBlock = new AxonMomentarySwitchLogicBlock();
				break;
			
			case AxonLatchingSwitchLogicBlock_t:
				axonLogicBlock = new AxonLatchingSwitchLogicBlock();
				break;
				
			case AxonVariableSwitchLogicBlock_t:
				axonLogicBlock = new AxonVariableSwitchLogicBlock();
				break;
				
			default:
				Serial.println( F(" ERROR: logicCode not supported") );
				break;
		}
		
		if (axonLogicBlock)
		{
			for( uint8_t i = 0; i < AxonLogicManager::actionSlotsPerLogicBlock; i++)
			{
				if (logicInfo.actionSlot[i] != 0)
				{
					uint8_t flags = (logicInfo.actionSlot[i]>>8) & 0xFC;
					uint16_t actionNumber = logicInfo.actionSlot[i] & 0x03FF;
					
					if ((flags & 0x80) == 0x80) { Serial.println("setOnAction"); axonLogicBlock->setOnAction( actionNumber ); }
					if ((flags & 0x40) == 0x40) { Serial.println("setOffAction"); axonLogicBlock->setOffAction( actionNumber ); }
					if ((flags & 0x20) == 0x20) { Serial.println("setChangeAction"); axonLogicBlock->setChangeAction( actionNumber ); }
				}
			}
		}
	}
	
	return( axonLogicBlock );
}


void AxonLogicManager::__REMOVE__check_written( uint16_t logicNumber )
{
	AxonLogicInfo_t logicInfo;
		
	if (getLogicBuffer( logicNumber, &logicInfo ) == NO_ERROR)
	{
		Serial.print( "LogicCode:" );
		Serial.println( logicInfo.logicCode, HEX );
		
		for(uint8_t i = 0; i < AxonLogicManager::actionSlotsPerLogicBlock; i++)
		{
			Serial.print( "Action");
			Serial.print( i );
			Serial.print( ":" );

			Serial.print( logicInfo.actionSlot[i], HEX );
			Serial.println();
		}
	}
	else
	{
		Serial.println( "ERROR whilst reading LogicBuffer" );
	}
}
