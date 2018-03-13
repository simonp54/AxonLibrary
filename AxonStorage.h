/* originally by Simon Peace
 * a wrapper for FRAM memory on the Axon
 * VERSION 4.0 15/02/2018
 */

#ifndef AXON_STORAGE_h
#define AXON_STORAGE_h

#include "Arduino.h"

class AxonStorage
{
	public:
		static AxonStorage *instance();

		static const uint32_t ADDRESS_SPACE_LOW;
		static const uint32_t ADDRESS_SPACE_HIGH;
		
		static const uint8_t NO_ERROR;
		static const uint8_t OUT_OF_BOUNDS;
		static const uint8_t CHUNK_FAILED;
		
		bool read( uint32_t fromAddr, void *data, uint32_t bytesToRead );
		bool read( uint32_t fromAddr, uint8_t *data );
		bool read( uint32_t fromAddr, uint16_t *data );
		bool write( uint32_t toAddr, const void *data, uint32_t bytesToWrite );
		bool write( uint32_t toAddr, uint8_t data );
		bool write( uint32_t toAddr, uint16_t data );
		uint8_t getError();
	protected:
		AxonStorage();
	private:
		static AxonStorage *_instance;
		
		
		static const uint8_t _FRAM_ADDRESSES[];
		static const uint32_t _FRAM_ADDRESS_RANGE_LOW;
		static const uint32_t _FRAM_ADDRESS_RANGE_HIGH;
		static const uint32_t _FRAM_MODULE_MASK;
		static const uint32_t _FRAM_ADDRESS_MASK;
		static const uint8_t _WIRE_BUFFER_SIZE;
		static const uint8_t _SINGLE_BYTE_SIZE;

		bool _boundsOK( uint32_t addr );
		uint32_t _overlap( uint32_t addr, uint32_t bytesToCheck );
		uint8_t _errorcode = NO_ERROR;
		void _FRAMStartWrite(uint8_t framModule, uint32_t framMem);
		void _FRAMStartRead(uint8_t framModule, uint32_t framMem);
};

#endif