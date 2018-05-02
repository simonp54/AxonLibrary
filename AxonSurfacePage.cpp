#include "AxonSurfacePage.h"
#include "AxonStorage.h"
#include "AxonKeyScanner.h"

#include "AxonDebugDefines.h"


uint32_t AxonSurfacePage::getSize()
{
//	Serial.print( F("AxonSurfacePage::getSize=") );
//	Serial.println( sizeof(_name) + (_switchPersistence[0].getSize() * _maxSwitches) );
	
	return ( sizeof(_name) + (_switchPersistence[0].getSize() * _maxSwitches) );
}

void AxonSurfacePage::setBaseAddress( uint32_t baseAddress )
{
	_baseAddress = baseAddress;
	_contextOK = true;

	for( uint8_t i = 0; i < _maxSwitches; i++ )
	{
		_switchPersistence[i].setBaseAddress( _baseAddress + sizeof(_name) + (i * _switchPersistence[i].getSize() ) );
	}
}



void AxonSurfacePage::format()
{
	if (_contextOK)
	{
#ifdef DEBUG_SURFACES
		Serial.print( F("AxonSurfacePage::format() from address 0x") );
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
		Serial.println( F("AxonSurfacePage::format baseAddress NOT SET") );
	}
}

void AxonSurfacePage::build()
{
	if (_contextOK)
	{
#ifdef DEBUG_SURFACES
		Serial.print( F("AxonSurfacePage::build from ") );
		Serial.println( _baseAddress, HEX );
#endif
		
		//read the name
		
		for( uint8_t i = 0; i < _maxSwitches; i++ )
		{
			_switchPersistence[i].build();
		}
	}
	else
	{
		Serial.println( F("AxonSurfacePage::build baseAddress NOT SET") );
	}
}

void AxonSurfacePage::activate()
{
	for (uint8_t i = 0; i < _maxSwitches; i++)
	{
		AxonKeyScanner::instance()->setOnKeyScan( i, _switchPersistence[i].logic() );
	}
}

AxonSwitchPersistence *AxonSurfacePage::switchIndex( uint8_t switchIndex )
{
	uint8_t tmp = constrain( switchIndex, 0, _maxSwitches );
	
	if (tmp != switchIndex) { return NULL; }
	
	return &_switchPersistence[switchIndex];
}