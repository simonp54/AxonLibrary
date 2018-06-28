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
	AxonStorage::instance()->format( _baseAddress, 0x00, maxLogicItems * sizeof(AxonLogicInfo_t) );
}

uint8_t AxonLogicManager::defineLogic( uint16_t logicSlot, const AxonLogicInfo_t *logicInfo )
{
	if ((logicSlot < 1) or (logicSlot > maxLogicItems))
	{
		return (INVALID_LOGIC_NUMBER);
	}	
	
	if (AxonStorage::instance()->write( _baseAddress + ((logicSlot-1) * sizeof(AxonLogicInfo_t)), logicInfo, sizeof( AxonLogicInfo_t ) ) )
	{
		return( NO_ERROR );
	}
	return (UNABLE_TO_WRITE);
}

uint8_t AxonLogicManager::getLogicBuffer( uint16_t logicSlot, AxonLogicInfo_t *logicInfo )
{
	if ((logicSlot < 1) or (logicSlot > maxLogicItems))
	{
		return( INVALID_LOGIC_NUMBER );
	}	
	
	if (AxonStorage::instance()->read( _baseAddress + ((logicSlot-1) * sizeof(AxonLogicInfo_t)), logicInfo, sizeof( AxonLogicInfo_t ) ) )
	{
		return( NO_ERROR );
	}
	return( UNABLE_TO_READ );
}


AxonLogicBlock *AxonLogicManager::createLogic( uint16_t logicSlot )
{
	AxonLogicInfo_t logicInfo;
	AxonLogicBlock *axonLogicBlock = NULL;
	
	if (getLogicBuffer( logicSlot, &logicInfo ) == NO_ERROR)
	{
		switch (logicInfo.logicCode)
		{
			case AxonMomentarySwitchLogicBlockCode:
				axonLogicBlock = new AxonMomentarySwitchLogicBlock();
				break;
			
			case AxonLatchingSwitchLogicBlockCode:
				axonLogicBlock = new AxonLatchingSwitchLogicBlock();
				break;
				
			case AxonVariableSwitchLogicBlockCode:
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
					
					if ((flags & 0x80) == 0x80) { axonLogicBlock->setOnAction( actionNumber ); }
					if ((flags & 0x40) == 0x40) { axonLogicBlock->setOffAction( actionNumber ); }
					if ((flags & 0x20) == 0x20) { axonLogicBlock->setChangeAction( actionNumber ); }
				}
			}
		}
	}
	
	return( axonLogicBlock );
}


void AxonLogicManager::__REMOVE__check_written( uint16_t logicSlot )
{
	AxonLogicInfo_t logicInfo;
		
	if (getLogicBuffer( logicSlot, &logicInfo ) == NO_ERROR)
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
