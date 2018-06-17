#ifndef AXON_ACTION_MANAGER_h
#define AXON_ACTION_MANAGER_h

#include "Arduino.h"

class AxonActionManager
{
	private:
		static AxonActionManager *_instance;
		
		static const uint32_t _baseAddress = 0x30000;
		static const uint16_t _maxActionItems = 1024;
		static const uint8_t _actionItemSize = 25;
	public:
		static const uint8_t NO_ERROR;
		static const uint8_t INVALID_ACTION_NUMBER;
		static const uint8_t UNABLE_TO_WRITE;

		static AxonActionManager *instance();
		
		void format();

		// format of buffer must be
		// actionType (uint8_t)
		// param1 (uint8_t)
		// param2 (uint8_t)
		// param3 (uint8_t)
		// param4 (uint8_t)
		// name (20 x uint8_t)  terminated with 0x00 values to fill the buffer
		
		uint8_t defineAction( uint16_t actionNumber, const uint8_t *actionDefinitionBuffer, uint8_t bufferSize );
		
		void executeAction( uint16_t actionNumber );
		
		void __REMOVE__check_written( uint16_t actionNumber );
	protected:
	    AxonActionManager();							// constructor
};

#endif