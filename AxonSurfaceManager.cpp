#include "AxonSurfaceManager.h"
#include "AxonLogicManager.h"
#include "AxonKeyScanner.h"
#include "AxonExprScanner.h"
#include "AxonStorage.h"
#include "AxonScribble.h"

#include "AxonDebugDefines.h"
#include "AxonCheckMem.h"

AxonSurfaceManager *AxonSurfaceManager::_instance = 0;

const uint8_t AxonSurfaceManager::NO_ERROR = 0;
const uint8_t AxonSurfaceManager::INVALID_SURFACE_NUMBER = 1;
const uint8_t AxonSurfaceManager::UNABLE_TO_WRITE = 2;
const uint8_t AxonSurfaceManager::UNABLE_TO_READ = 3;

const uint8_t AxonSurfaceManager::_mapHardwareInterface[] = { 0, 1, 2, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 255, 255, 255, 255 };


AxonSurfaceManager *AxonSurfaceManager::instance()
{
	if (!_instance)
	{
		_instance = new AxonSurfaceManager();
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
	}
	return _instance;
}

/*
 *  CONSTRUCTOR FOR CLASS
 */
AxonSurfaceManager::AxonSurfaceManager()
{
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
#ifdef DEBUG_LISTS
	Serial.println( F("AxonSurfaceManager::ctor") );
#endif
}

void AxonSurfaceManager::processOutstanding()
{
	if (_surfaceQueued)
	{
		_surfaceQueued = false;
		loadSurface( _qSurfaceNumber );
	}
}

void AxonSurfaceManager::format()
{
	AxonStorage::instance()->format( _baseAddress, 0x00, (maxSurfaceItems * sizeof(AxonSurfaceInfo_t)) );
}

uint8_t AxonSurfaceManager::defineSurface( uint8_t surfaceNumber, const AxonSurfaceInfo_t *surfaceInfo )
{
	if ((surfaceNumber < 1) or (surfaceNumber > maxSurfaceItems))
	{
		return( INVALID_SURFACE_NUMBER );
	}	
	
	if (AxonStorage::instance()->write( _baseAddress + ((surfaceNumber-1) * sizeof(AxonSurfaceInfo_t)), surfaceInfo, sizeof(AxonSurfaceInfo_t) ))
	{
		return( NO_ERROR );
	}
	return( UNABLE_TO_WRITE );
}

uint8_t AxonSurfaceManager::getSurfaceBuffer( uint8_t surfaceNumber, AxonSurfaceInfo_t *surfaceInfo )
{
	if ((surfaceNumber < 1) or (surfaceNumber > maxSurfaceItems))
	{
		return( INVALID_SURFACE_NUMBER );
	}	
	
	if (AxonStorage::instance()->read( _baseAddress + ((surfaceNumber-1) * sizeof(AxonSurfaceInfo_t)), surfaceInfo, sizeof(AxonSurfaceInfo_t) ))
	{
		return( NO_ERROR );
	}
	return( UNABLE_TO_READ );
}

void AxonSurfaceManager::dropAllLogicBlocks()
{
	for( uint8_t i = 0; i < hardwareInterfacesPerSystem; i++ )
	{
		if (_logicBlockList[i] != NULL)
		{
			delete( _logicBlockList[i] );
			_logicBlockList[i] = NULL;
		}
	}
}

void AxonSurfaceManager::qSurface( uint8_t surfaceNumber )
{
	_qSurfaceNumber = surfaceNumber;
	_surfaceQueued = true;
}


void AxonSurfaceManager::loadSurface( uint8_t surfaceNumber )
{	
	AxonSurfaceInfo_t surfaceInfo;

	AxonScribble::instance()->selectAll();
	AxonScribble::instance()->clearBuffer();          // clear the internal memory
	AxonScribble::instance()->sendBuffer();
	
	if (getSurfaceBuffer( surfaceNumber, &surfaceInfo ) == NO_ERROR )
	{
		_currentSurfaceNumber = surfaceNumber;
		AxonKeyScanner::instance()->unlinkAllKeyScan();
		AxonExprScanner::instance()->unlinkAllExprScan();
		
		dropAllLogicBlocks();
		
		for(uint8_t i = 0; i < hardwareInterfacesPerSystem; i++)
		{
			if (surfaceInfo.hardwareInterface[i] != 0)
			{
				//Create new Logic Block
				_logicBlockList[i] = AxonLogicManager::instance()->createLogic( surfaceInfo.hardwareInterface[i], _mapHardwareInterface[i] );
				
				if ( _logicBlockList[i] != NULL )
				{
					if ( i < 22 )
					{
						AxonKeyScanner::instance()->setOnKeyScan( _mapHardwareInterface[i], _logicBlockList[i] );
					}
					if ( i > 21 )
					{
						AxonExprScanner::instance()->setOnExprScan( i-22, _logicBlockList[i] );
					}
				}
			}
		}
	}
}


void AxonSurfaceManager::__REMOVE__check_written( uint8_t surfaceNumber )
{
	AxonSurfaceInfo_t surfaceInfo;
		
	if (getSurfaceBuffer( surfaceNumber, &surfaceInfo ) == NO_ERROR)
	{
		Serial.print( "SURFACE DEFINITION:");
		Serial.println( surfaceNumber );

		for (uint8_t i = 0; i < hardwareInterfacesPerSystem; i++)
		{
			Serial.print( "hardwareInterface[");
			Serial.print( i );
			Serial.print( "]=" );
			Serial.println( surfaceInfo.hardwareInterface[i] );
		}
	}
	else
	{
		Serial.println( "ERROR whilst reading SurfaceBuffer" );
	}
}
