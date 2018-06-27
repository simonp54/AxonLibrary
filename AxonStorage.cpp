/* originally by Simon Peace
 * a wrapper for FRAM memory on the Axon
 * VERSION 4.0 15/02/2018
 */
 
#include "Arduino.h"
#include "AxonStorage.h"
#include "wire.h"

#include "AxonDebugDefines.h"
#include "AxonCheckMem.h"

AxonStorage *AxonStorage::_instance = 0;

const uint32_t AxonStorage::ADDRESS_SPACE_LOW = 0x00000;
const uint32_t AxonStorage::ADDRESS_SPACE_HIGH = 0x7FFFF;
	
const uint8_t AxonStorage::NO_ERROR = 0;
const uint8_t AxonStorage::OUT_OF_BOUNDS = 1;
const uint8_t AxonStorage::CHUNK_FAILED = 2;

const uint8_t AxonStorage::_FRAM_ADDRESSES[8] = { 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57 };
const uint32_t AxonStorage::_FRAM_ADDRESS_RANGE_LOW = 0x0000;
const uint32_t AxonStorage::_FRAM_ADDRESS_RANGE_HIGH = 0xFFFF;
const uint32_t AxonStorage::_FRAM_MODULE_MASK = 0x0F0000;
const uint32_t AxonStorage::_FRAM_ADDRESS_MASK = 0x00FFFF;
const uint8_t AxonStorage::_WIRE_BUFFER_SIZE = 28;
const uint8_t AxonStorage::_SINGLE_BYTE_SIZE = 1;

/*
 * Singleton accessor function
 */
AxonStorage *AxonStorage::instance()
{
	if (!_instance)
	{
		_instance = new AxonStorage();
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
	}
	return _instance;
}

/*
 *  CONSTRUCTOR FOR CLASS
 */
AxonStorage::AxonStorage()
{
	if (TWCR == 0) // do this check so that Wire only gets initialized once
	{
		Wire.begin();
	}
	
	_errorcode = NO_ERROR;
}

/*
 *  WRITE A BUFFER TO THE MEMORY SPACE, SPLIT AS REQUIRED ACROSS BOUNDARIES
 *  AND CHECK BOUNDARY CONDITIONS BEFORE WRITE
 */
bool AxonStorage::write( uint32_t toAddr, const void *data, uint32_t bytesToWrite )
{
	const uint8_t *byteptr = data;
	
	_errorcode = NO_ERROR;				// reset errorcode to no error whenever we start the write process
#ifdef AXONSTORAGE_DEBUG
	Serial.printf( "AxonStorage.write( toaddr=0x%5.5lX, data, bytesToWrite=0x%5.5lX)\n", toAddr, bytesToWrite );
#endif
	
	// check bounds of toAddr
	// effectively, this checks the start address is in range AND
	// the end of the area required to store the data is also in range
	if ( (!_boundsOK(toAddr)) || (!_boundsOK(toAddr + bytesToWrite - 1)))
	{
		_errorcode = OUT_OF_BOUNDS;
		return false;
	}
		
	// check boundary overlap
	uint32_t overlapbytes = _overlap( toAddr, bytesToWrite );
	if (overlapbytes > 0)
	{
#ifdef AXONSTORAGE_DEBUG
		Serial.printf("AxonStorage._overlap = 0x%5.5lX\n", overlapbytes );
#endif
		// recursively call this function to 
		// write the additional section(s) and then
		// modify bytesToWrite and toAddr accordingly
		if ( !write( toAddr, byteptr, bytesToWrite - overlapbytes ) )
		{
			_errorcode = CHUNK_FAILED;
			return( false );
		}
		
		byteptr += bytesToWrite - overlapbytes;						// move the pointer past the bytes we already stored
		toAddr += bytesToWrite - overlapbytes;						// adjust the address for where the remaining block will be written (usually 0x10000 or similar)
		bytesToWrite = overlapbytes;							    // adjust bytesToWrite
#ifdef AXONSTORAGE_DEBUG
		Serial.printf("AxonStorage adjusted params, toAddr=0x%5.5lX, bytesToWrite 0x%5.5lX\n", toAddr, bytesToWrite );
#endif
	}

	// ok to write out to FRAM now
	uint32_t FRAMoffset = (toAddr & _FRAM_ADDRESS_MASK);											// the bottom two bytes of the address give the FRAM memory unit address
	uint8_t FRAMmodule = AxonStorage::_FRAM_ADDRESSES[((toAddr & _FRAM_MODULE_MASK) >> 16)];		// the low half of the top byte (3) gives the FRAM module number

#ifdef AXONSTORAGE_DEBUG
	Serial.printf( "writing to FRAMmodule 0x%2.2X, at address 0x%5.5lX\n", FRAMmodule, FRAMoffset);
	Serial.printf( "%d\n", bytesToWrite );
#endif
	
	_FRAMStartWrite( FRAMmodule, FRAMoffset );

	for( uint32_t bytecounter = 0; bytecounter < bytesToWrite; bytecounter++)
	{
#ifdef AXONSTORAGE_DEBUG
		Serial.printf( "0x%X ", *(const uint8_t *)byteptr );
#endif
		Wire.write( *byteptr++ );

		if ((bytecounter+1) % _WIRE_BUFFER_SIZE == 0)				// the WIRE library has a buffer of about 30 bytes
																	// so we need to start a new WIRE transmission every so often
		{
#ifdef AXONSTORAGE_DEBUG
		Serial.println( );
#endif
			// start a new I2C transaction because of buffer size
			Wire.endTransmission();
			_FRAMStartWrite( FRAMmodule, FRAMoffset + bytecounter + 1 );
		}
	}
	Wire.endTransmission();
#ifdef AXONSTORAGE_DEBUG
		Serial.println( );
#endif
	
	return(true);
}

/*
 *  OVERLOADED WRITE for UINT8_T
 */
bool AxonStorage::write( uint32_t toAddr, uint8_t data )
{
	return write( (uint32_t)toAddr, (const void*)&data, sizeof(uint8_t) );
}

/*
 *  OVERLOADED WRITE for UINT16_T
 */
bool AxonStorage::write( uint32_t toAddr, uint16_t data )
{
	return write( (uint32_t)toAddr, (const void*)&data, sizeof(uint16_t) );
}


/*
 *  CHECK WHETHER THE ADDRESS PASSED IS WITHIN THE BOUNDS REQUIRED
 */
bool AxonStorage::_boundsOK( uint32_t addr )
{
	if ((addr >= AxonStorage::ADDRESS_SPACE_LOW) && (addr <= AxonStorage::ADDRESS_SPACE_HIGH))
	{
#ifdef AXONSTORAGE_DEBUG_BOUNDS_CHECK
		Serial.printf("_boundsOK check passed, 0x%5.5lX, 0x%5.5lX, 0x%5.5lX\n", addr, AxonStorage::ADDRESS_SPACE_LOW, AxonStorage::ADDRESS_SPACE_HIGH);
#endif
		return(true);
	}
	else
	{
#ifdef AXONSTORAGE_DEBUG_BOUNDS_CHECK
		Serial.printf("_boundsOK check failed, 0x%5.5lX, 0x%5.5lX, 0x%5.5lX\n", addr, AxonStorage::ADDRESS_SPACE_LOW, AxonStorage::ADDRESS_SPACE_HIGH);
#endif
		return(false);
	}
}

/*
 *  SEE IF THE BUFFER WILL OVERLAP THE NEXT FRAM BOUNDARY
 *  RETURN THE NUMBER OF BYTES THAT WILL OVERLAP (ZERO OFFSET ARRAY)
 */
uint32_t AxonStorage::_overlap( uint32_t addr, uint32_t bytesToCheck )
{
	uint32_t framSubAddr = (addr & AxonStorage::_FRAM_ADDRESS_RANGE_HIGH);
	if ( ( framSubAddr + bytesToCheck) > AxonStorage::_FRAM_ADDRESS_RANGE_HIGH )
	{
		return ( framSubAddr + bytesToCheck - AxonStorage::_FRAM_ADDRESS_RANGE_HIGH - 1 );
	}
	else
	{
		return ( 0 );
	}
}

/*
 *  READ FROM THE FRAMs THE BUFFER SIZE REQUIRED
 *  ACCOUNT FOR FRAM MODULE BOUNDARIES
 *  AND ALSO CHECK THE ADDRESS REQUESTED IS VALID BEFORE READING
 */
bool AxonStorage::read( uint32_t fromAddr, void *data, uint32_t bytesToRead )
{
	uint8_t *byteptr = data;
	
	_errorcode = NO_ERROR;				// reset error code when we start a read process
#ifdef AXONSTORAGE_DEBUG
	Serial.printf( "AxonStorage.read( fromAddr=0x%5.5lX, data, bytesToRead=0x%5.5lX)\n", fromAddr, bytesToRead );
#endif
	// check bounds of fromAddr
	if ( (!_boundsOK(fromAddr)) || (!_boundsOK(fromAddr + bytesToRead-1)))
	{
		_errorcode = OUT_OF_BOUNDS;
		return( false );
	}

	// check boundary overlap
	uint32_t overlapbytes = _overlap( fromAddr, bytesToRead );
	if (overlapbytes > 0)
	{
#ifdef AXONSTORAGE_DEBUG
		Serial.printf("AxonStorage._overlap = 0x%5.5lX\n", overlapbytes );
#endif
		// recursively call this function to 
		// read the additional section(s) and then
		// modify bytesToRead and fromAddr accordingly
		if ( !read( fromAddr, byteptr, bytesToRead - overlapbytes ) )
		{
			_errorcode = CHUNK_FAILED;
			return( false );
		}
		
		byteptr += bytesToRead - overlapbytes;				// move the pointer past the bytes we already read
		fromAddr += bytesToRead - overlapbytes;				// adjust the address for where the remaining block will be read (usually 0x10000 or similar)
		bytesToRead = overlapbytes;							// adjust bytesToRead
#ifdef AXONSTORAGE_DEBUG
		Serial.print( F("AxonStorage adjusted params, fromAddr=0x") );
		Serial.print( fromAddr, HEX );
		Serial.print( F(", bytesToRead 0x") );
		Serial.println( bytesToRead, HEX );
#endif
	}
	
	// ok to read out to FRAM now
	uint32_t FRAMoffset = (fromAddr & _FRAM_ADDRESS_MASK);
	uint8_t FRAMmodule = AxonStorage::_FRAM_ADDRESSES[((fromAddr & _FRAM_MODULE_MASK) >> 16)];

#ifdef AXONSTORAGE_DEBUG
	Serial.print( F("reading from FRAMmodule 0x") );
	Serial.print( FRAMmodule, HEX );
	Serial.print( F(", at address 0x") );
	Serial.println( FRAMoffset, HEX );
	Serial.print( F("bytes to read=") );
	Serial.println( bytesToRead, HEX );
#endif	
	_FRAMStartRead( FRAMmodule, FRAMoffset );

	for( uint32_t bytecounter = 0; bytecounter < bytesToRead; bytecounter++ )
	{
		Wire.requestFrom( FRAMmodule, _SINGLE_BYTE_SIZE );
		uint8_t foo = Wire.read();
		*byteptr++ = foo;
	}
#ifdef AXONSTORAGE_DEBUG
	Serial.println();
#endif	
	return( true );
}

/*
 *  OVERLOADED READ for UINT8_T
 */
bool AxonStorage::read( uint32_t fromAddr, uint8_t *data )
{
	return read( (uint32_t)fromAddr, data, sizeof(uint8_t) );
}

/*
 *  OVERLOADED READ for UINT16_T
 */
bool AxonStorage::read( uint32_t fromAddr, uint16_t *data )
{
	return read( (uint32_t)fromAddr, data, sizeof(uint16_t) );
}

/*
 * "format" a section of FRAM memory.
 */
bool AxonStorage::format( uint32_t toAddr, uint8_t val, uint32_t bytesToWrite )
{
	// ok to write out to FRAM now
	uint32_t FRAMoffset = (toAddr & _FRAM_ADDRESS_MASK);											// the bottom two bytes of the address give the FRAM memory unit address
	uint8_t FRAMmodule = AxonStorage::_FRAM_ADDRESSES[((toAddr & _FRAM_MODULE_MASK) >> 16)];		// the low half of the top byte (3) gives the FRAM module number

#ifdef AXONSTORAGE_DEBUG
	Serial.printf( "writing to FRAMmodule 0x%2.2X, at address 0x%5.5lX\n", FRAMmodule, FRAMoffset);
	Serial.printf( "%d\n", bytesToWrite );
#endif
	
	_FRAMStartWrite( FRAMmodule, FRAMoffset );

	for( uint32_t bytecounter = 0; bytecounter < bytesToWrite; bytecounter++)
	{
		Wire.write( val );

		if ((bytecounter+1) % _WIRE_BUFFER_SIZE == 0)				// the WIRE library has a buffer of about 30 bytes
																	// so we need to start a new WIRE transmission every so often
		{
			// start a new I2C transaction because of buffer size
			Wire.endTransmission();
			_FRAMStartWrite( FRAMmodule, FRAMoffset + bytecounter + 1 );
		}
	}
	Wire.endTransmission();
#ifdef AXONSTORAGE_DEBUG
		Serial.println( );
#endif
	
	return(true);
}

/*
 *  RETURN THE ERROR CODE IF REQUESTED BY CLIENT
 */
uint8_t AxonStorage::getError()
{
	return( _errorcode );
}

/*
 *  LOW LEVEL WIRE FUNCTIONS REQUIRED CONTROL TO INTERFACE TO THE FRAM
 */
void AxonStorage::_FRAMStartWrite(uint8_t FRAMmodule, uint32_t FRAMoffset)
{  
  Wire.beginTransmission( FRAMmodule );   // start condition and address  1010 000
  Wire.write( FRAMoffset >> 8 );           // address high 8bits           0000 0000
  Wire.write( FRAMoffset & 0xFF );         // address low 8bits            0000 0000
}

/*
 *  LOW LEVEL WIRE FUNCTION TO READ FRAM, uses _FRAMStartWrite AS THE SAME
 *  EXCEPT FOR ENDING THE TRANSMISSION...
 */
void AxonStorage::_FRAMStartRead(uint8_t FRAMmodule, uint32_t FRAMoffset)
{
  _FRAMStartWrite( FRAMmodule, FRAMoffset );
  Wire.endTransmission();
}