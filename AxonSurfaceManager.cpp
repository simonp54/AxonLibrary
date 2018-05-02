#include "AxonSurfaceManager.h"
#include "AxonStorage.h"

#include "AxonDebugDefines.h"
#include "AxonCheckMem.h"

AxonSurfaceManager *AxonSurfaceManager::_instance = 0;

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
#ifdef DEBUG_SURFACES
	Serial.println( F("AxonSurfaceManager::ctor") );
#endif
	_surface.setBaseAddress( _baseAddress + (0 * _surface.getSize()) );
}

uint32_t AxonSurfaceManager::getSize()
{
	return (_surface.getSize() * _maxSurfaces);
}

void AxonSurfaceManager::format()
{
#ifdef DEBUG_SURFACES
	Serial.print( F("AxonSurfaceManager::format() from address 0x") );
	Serial.print( _baseAddress, HEX );
	Serial.print( F(" filling with 0x00 for 0x") );
	Serial.print( getSize(), HEX );
	Serial.println( F(" bytes") );
#endif
	
	// set my stuff to zeros
	AxonStorage::instance()->format( _baseAddress, 0x00, getSize() );
}

AxonSurface *AxonSurfaceManager::surface( uint8_t slotNumber )
{
#ifdef DEBUG_SURFACES
	Serial.println( F("AxonSurfaceManager::surface") );
#endif
	_slotNumber = constrain( slotNumber, 0, _maxSurfaces - 1 );

	_surface.setBaseAddress( _baseAddress + (_slotNumber * _surface.getSize()) );

	return &_surface;
}