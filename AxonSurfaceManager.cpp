#include "AxonSurfaceManager.h"
#include "AxonLogicManager.h"
#include "AxonKeyScanner.h"
#include "AxonExprScanner.h"
#include "AxonStorage.h"

#include "AxonDebugDefines.h"
#include "AxonCheckMem.h"

AxonSurfaceManager *AxonSurfaceManager::_instance = 0;

const uint8_t AxonSurfaceManager::NO_ERROR = 0;
const uint8_t AxonSurfaceManager::INVALID_SURFACE_NUMBER = 1;
const uint8_t AxonSurfaceManager::UNABLE_TO_WRITE = 2;
const uint8_t AxonSurfaceManager::UNABLE_TO_READ = 3;

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
		if (_logicBlockList[i])
		{
			delete( _logicBlockList[i] );
		}
	}
}


void AxonSurfaceManager::loadSurface( uint8_t surfaceNumber )
{	
Serial.print(F("AxonSurfaceManager::loadSurface("));
Serial.print( surfaceNumber );
Serial.println( F(")") );
	AxonSurfaceInfo_t surfaceInfo;
	
	if (getSurfaceBuffer( surfaceNumber, &surfaceInfo ) == NO_ERROR )
	{
		_currentSurfaceNumber = surfaceNumber;
		AxonKeyScanner::instance()->unlinkAllKeyScan();
		AxonExprScanner::instance()->unlinkAllExprScan();
		
		dropAllLogicBlocks();
		
		//AxonDisplayManager::instance()->dropAll();
		
		for(uint8_t i = 0; i < hardwareInterfacesPerSystem; i++)
		{
			//Create new Logic Block
			_logicBlockList[i] = AxonLogicManager::instance()->createLogic( surfaceInfo.hardwareInterface[i] );
			
			if ( _logicBlockList[i] )
			{
				switch(i)
				{
					case 0:		AxonKeyScanner::instance()->setOnKeyScan( 0, _logicBlockList[i] );		break;
					case 1:		AxonKeyScanner::instance()->setOnKeyScan( 1, _logicBlockList[i] );		break;
					case 2:		AxonKeyScanner::instance()->setOnKeyScan( 2, _logicBlockList[i] );		break;
					case 3:		AxonKeyScanner::instance()->setOnKeyScan( 5, _logicBlockList[i] );		break;
					case 4:		AxonKeyScanner::instance()->setOnKeyScan( 6, _logicBlockList[i] );		break;
					case 5:		AxonKeyScanner::instance()->setOnKeyScan( 7, _logicBlockList[i] );		break;
					case 6:		AxonKeyScanner::instance()->setOnKeyScan( 8, _logicBlockList[i] );		break;
					case 7:		AxonKeyScanner::instance()->setOnKeyScan( 9, _logicBlockList[i] );		break;
					case 8:		AxonKeyScanner::instance()->setOnKeyScan( 10, _logicBlockList[i] );		break;
					case 9:		AxonKeyScanner::instance()->setOnKeyScan( 11, _logicBlockList[i] );		break;
					case 10:	AxonKeyScanner::instance()->setOnKeyScan( 12, _logicBlockList[i] );		break;
					case 11:	AxonKeyScanner::instance()->setOnKeyScan( 13, _logicBlockList[i] );		break;
					case 12:	AxonKeyScanner::instance()->setOnKeyScan( 14, _logicBlockList[i] );		break;
					case 13:	AxonKeyScanner::instance()->setOnKeyScan( 15, _logicBlockList[i] );		break;
					case 14:	AxonKeyScanner::instance()->setOnKeyScan( 16, _logicBlockList[i] );		break;
					case 15:	AxonKeyScanner::instance()->setOnKeyScan( 17, _logicBlockList[i] );		break;
					case 16:	AxonKeyScanner::instance()->setOnKeyScan( 18, _logicBlockList[i] );		break;
					case 17:	AxonKeyScanner::instance()->setOnKeyScan( 19, _logicBlockList[i] );		break;
					case 18:	AxonKeyScanner::instance()->setOnKeyScan( 20, _logicBlockList[i] );		break;
					case 19:	AxonKeyScanner::instance()->setOnKeyScan( 21, _logicBlockList[i] );		break;
					case 20:	AxonKeyScanner::instance()->setOnKeyScan( 22, _logicBlockList[i] );		break;
					case 21:	AxonKeyScanner::instance()->setOnKeyScan( 23, _logicBlockList[i] );		break;
					
					case 22:	AxonExprScanner::instance()->setOnExprScan( 0, _logicBlockList[i] );	break;
					case 23:	AxonExprScanner::instance()->setOnExprScan( 1, _logicBlockList[i] );	break;
					case 24:	AxonExprScanner::instance()->setOnExprScan( 2, _logicBlockList[i] );	break;
					case 25:	AxonExprScanner::instance()->setOnExprScan( 3, _logicBlockList[i] );	break;
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
