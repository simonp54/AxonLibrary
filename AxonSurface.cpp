#include "AxonSurface.h"
#include "AxonStorage.h"

#include "AxonDebugDefines.h"

uint32_t AxonSurface::getSize()
{
//	Serial.print( F("AxonSurface::getSize=") );
//	Serial.println( _page[0].getSize() + _page[1].getSize() );
	
	return ( 24 + _page[0].getSize() + _page[1].getSize() );
}

void AxonSurface::setBaseAddress( uint32_t baseAddress )
{
	_baseAddress = baseAddress;
	_contextOK = true;

	_page[0].setBaseAddress( _baseAddress + 24 );
	_page[1].setBaseAddress( _baseAddress + 24 + _page[0].getSize() );
}


void AxonSurface::format()
{
	if (_contextOK)
	{
#ifdef DEBUG_SURFACES
		Serial.print( F("AxonSurface::format() from address 0x") );
		Serial.print( _baseAddress, HEX );
		Serial.print( F(" filling with 0x00 for 0x") );
		Serial.print( getSize(), HEX );
		Serial.println( F(" bytes") );
#endif
		
		// set my stuff to zeros
		AxonStorage::instance()->format( _baseAddress, 0x00, getSize() );
	}
	else
	{
		Serial.println( F("AxonSurface::format baseAddress NOT SET") );
	}
}

void AxonSurface::build()
{
	if (_contextOK)
	{
#ifdef DEBUG_SURFACES
		Serial.print( F("AxonSurface::build from ") );
		Serial.println( _baseAddress, HEX );
#endif
		
		for( uint8_t i = 0; i < _maxPages; i++)
		{
			_page[i].build();
		}
		
		_page[_currentPage].activate();
	}
	else
	{
		Serial.println( F("AxonSurface::build baseAddress NOT SET") );
	}
}

AxonSurfacePage *AxonSurface::page( uint8_t index )
{
	uint8_t tmp = constrain( index, 0, _maxPages );
	
	if (tmp != index) { return NULL; }
	
	return &_page[_currentPage];	
}

void AxonSurface::swapPage()
{
	_currentPage == 0 ? _currentPage = 1 : _currentPage = 0;
	
//	_page[_currentPage].activate();
}