#include "AxonLogicManager.h"
#include "AxonStorage.h"

#include "AxonLatchingSwitchLogicBlock.h"
#include "AxonMomentarySwitchLogicBlock.h"
#include "AxonVariableSwitchLogicBlock.h"

#include "AxonLabelDisplayBlock.h"

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


AxonLogicBlock *AxonLogicManager::createLogic( uint16_t logicSlot, uint8_t scribbleID )
{
	AxonLogicInfo_t logicInfo;
	AxonLogicBlock *axonLogicBlock = NULL;
	
	if (getLogicBuffer( logicSlot, &logicInfo ) == NO_ERROR)
	{
		switch (logicInfo.logicCode)
		{
			case AxonMomentarySwitchLogicBlockCode:
			{
				axonLogicBlock = new AxonMomentarySwitchLogicBlock();
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
				break;
			}
			
			case AxonLatchingSwitchLogicBlockCode:
			{
				axonLogicBlock = new AxonLatchingSwitchLogicBlock();
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
				break;
			}
			
			case AxonVariableSwitchLogicBlockCode:
			{
				axonLogicBlock = new AxonVariableSwitchLogicBlock();
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
				break;
			}
			
			default:
			{
				Serial.println( F(" ERROR: logicCode not supported") );
				break;
			}
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

			// only if the scribbleID is one of the scribble screens
			if (scribbleID <= 23)
			{
				switch (logicInfo.displayCode)
				{
					case AxonLabelDisplayBlockCode:
					{
						AxonDisplayBlock *tmp = new AxonLabelDisplayBlock( scribbleID, logicInfo.param2, logicInfo.param3, logicInfo.param4 );
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
						axonLogicBlock->setDisplayBlock( tmp );
						break;
					}	
					default:
					{
						Serial.println( F(" ERROR: displayCode not supported") );
						break;
					}
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
		Serial.print( "displayCode:" );
		Serial.println( logicInfo.displayCode );
		Serial.print( "param1:" );
		Serial.println( logicInfo.param1 );
		Serial.print( "param2:" );
		Serial.println( logicInfo.param2 );
		Serial.print( "param3:" );
		Serial.println( logicInfo.param3 );
		Serial.print( "param4:" );
		Serial.println( logicInfo.param4 );
		
		Serial.print( "Actions: ");
		for(uint8_t i = 0; i < AxonLogicManager::actionSlotsPerLogicBlock; i++)
		{
			Serial.print( "0x" );
			Serial.print( logicInfo.actionSlot[i], HEX );
			Serial.print( " " );
		}
		Serial.println();
	}
	else
	{
		Serial.println( "ERROR whilst reading LogicBuffer" );
	}
}
