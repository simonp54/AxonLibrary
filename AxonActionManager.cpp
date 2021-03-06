#include "AxonActionManager.h"
#include "AxonStorage.h"
#include "AxonAction.h"

#include "AxonSendMidiCCAction.h"
#include "AxonSendMidiFixedCCAction.h"
#include "AxonSendMidiPCAction.h"

#include "AxonContrastDownAction.h"
#include "AxonContrastSetAction.h"
#include "AxonContrastUpAction.h"

#include "AxonNextSurfaceAction.h"
#include "AxonPreviousSurfaceAction.h"

#include "AxonDebugDefines.h"
#include "AxonCheckMem.h"

AxonActionManager *AxonActionManager::_instance = 0;

const uint8_t AxonActionManager::NO_ERROR = 0;
const uint8_t AxonActionManager::INVALID_ACTION_SLOT = 1;
const uint8_t AxonActionManager::UNABLE_TO_WRITE = 2;
const uint8_t AxonActionManager::UNABLE_TO_READ = 3;

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
	AxonStorage::instance()->format( _baseAddress, 0x00, ( (maxActionItems + maxOverrideActionItems) * sizeof(AxonActionInfo_t) ) );
}

uint8_t AxonActionManager::writeAction( uint16_t actionSlot, const AxonActionInfo_t *actionInfo )
{
	if (AxonStorage::instance()->write( _baseAddress + ((actionSlot-1) * sizeof(AxonActionInfo_t)), actionInfo, sizeof(AxonActionInfo_t) ))
	{
		return( NO_ERROR );
	}
	return( UNABLE_TO_WRITE );
}

uint8_t AxonActionManager::defineAction( uint16_t actionSlot, const AxonActionInfo_t *actionInfo )
{
	if ((actionSlot < 1) or (actionSlot > maxActionItems))
	{
		return( INVALID_ACTION_SLOT );
	}

	return( writeAction( actionSlot, actionInfo ) );
}

uint8_t AxonActionManager::defineOverrideAction( uint16_t overrideSlot, const AxonActionInfo_t *actionInfo )
{
	if ((overrideSlot < 1) or (overrideSlot > maxOverrideActionItems))
	{
		return( INVALID_ACTION_SLOT );
	}	

	return( writeAction( maxActionItems + overrideSlot, actionInfo ) );
}


uint8_t AxonActionManager::getActionInfo( uint16_t actionSlot, AxonActionInfo_t *actionInfo )
{
	if ((actionSlot < 1) or (actionSlot > maxActionItems))
	{
		return( INVALID_ACTION_SLOT );
	}	
	
	if (AxonStorage::instance()->read( _baseAddress + ((actionSlot-1) * sizeof(AxonActionInfo_t)), actionInfo, sizeof(AxonActionInfo_t) ))
	{
		return( NO_ERROR );
	}
	return( UNABLE_TO_READ );
}

uint8_t AxonActionManager::getShortActionInfo( uint16_t actionSlot, AxonActionInfoNoName_t *actionInfo )
{
	if ((actionSlot < 1) or (actionSlot > maxActionItems))
	{
		return( INVALID_ACTION_SLOT );
	}	
	
	if (AxonStorage::instance()->read( _baseAddress + ((actionSlot-1) * sizeof(AxonActionInfo_t)), actionInfo, sizeof(AxonActionInfoNoName_t) ))
	{
		return( NO_ERROR );
	}
	return( UNABLE_TO_READ );
}

void AxonActionManager::executeAction( uint16_t actionSlot, AxonEvent *event )
{
	if ((actionSlot >= 1) and (actionSlot <= maxActionItems))
	{
		AxonActionInfoNoName_t actionInfo;
				
		if (getShortActionInfo( actionSlot, &actionInfo ) == NO_ERROR )
		{
			switch (actionInfo.actionCode)
			{
				case AxonSendMidiCCActionCode:
				{
					AxonAction *tmp = new AxonSendMidiCCAction( actionInfo.param1, actionInfo.param2, actionInfo.param3 );
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
					tmp->execute( NULL, event );
					delete tmp;
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
					break;
				}
				case AxonSendMidiFixedCCActionCode:
				{
					AxonAction *tmp = new AxonSendMidiFixedCCAction( actionInfo.param1, actionInfo.param2, actionInfo.param3, actionInfo.param4 );
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
					tmp->execute( NULL, event );
					delete tmp;
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
					break;
				}
				case AxonSendMidiPCActionCode:
				{
					AxonAction *tmp = new AxonSendMidiPCAction( actionInfo.param1, actionInfo.param2, actionInfo.param3 );
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
					tmp->execute( NULL, event );
					delete tmp;
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
					break;
				}
				case AxonContrastDownActionCode:
				{
					AxonAction *tmp = new AxonContrastDownAction();
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
					tmp->execute( NULL, event );
					delete tmp;
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
					break;
				}
				case AxonContrastSetActionCode:
				{
					AxonAction *tmp = new AxonContrastSetAction();
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
					tmp->execute( NULL, event );
					delete tmp;
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
					break;
				}
				case AxonContrastUpActionCode:
				{
					AxonAction *tmp = new AxonContrastUpAction();
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
					tmp->execute( NULL, event );
					delete tmp;
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
					break;
				}
				case AxonNextSurfaceActionCode:
				{
					AxonAction *tmp = new AxonNextSurfaceAction();
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
					tmp->execute( NULL, event );
					delete tmp;
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
					break;
				}
				case AxonPreviousSurfaceActionCode:
				{
					AxonAction *tmp = new AxonPreviousSurfaceAction();
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
					tmp->execute( NULL, event );
					delete tmp;
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
					break;
				}

				default:
				{
					Serial.println( "UNKNOWN actionCode" );
					break;
				}
			}
		}
	}
}


void AxonActionManager::__REMOVE__check_written( uint16_t actionSlot )
{
	AxonActionInfo_t actionInfo;
		
	if (getActionInfo( actionSlot, &actionInfo ) == NO_ERROR)
	{
		Serial.print( "actionCode:");
		Serial.println( actionInfo.actionCode );
		
		Serial.print( "Param1:");
		Serial.println( actionInfo.param1 );

		Serial.print( "Param2:");
		Serial.println( actionInfo.param2 );

		Serial.print( "Param3:");
		Serial.println( actionInfo.param3 );

		Serial.print( "Param4:");
		Serial.println( actionInfo.param4 );
	}
	else
	{
		Serial.println( "ERROR whilst reading ActionBuffer" );
	}
	
}
