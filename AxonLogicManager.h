#ifndef AXON_LOGIC_MANAGER_h
#define AXON_LOGIC_MANAGER_h

#include "Arduino.h"

class AxonLogicManager
{
	private:
		static AxonLogicManager *_instance;
		
		static const uint32_t _baseAddress = 0x36400;
		static const uint16_t _maxLogicItems = 1024;
		static const uint8_t _logicItemSize = 64;
	public:
		static const uint8_t NO_ERROR;
		static const uint8_t INVALID_LOGIC_NUMBER;
		static const uint8_t UNABLE_TO_WRITE;

		static AxonLogicManager *instance();
		
		void format();

		// format of buffer must be
		// logicType (uint8_t)
		// actionNumber1 (uint16_t)
		// actionNumber2 (uint16_t)
		//   :     :        :
		// actionNumber32 (uint16_t)
		
		uint8_t defineLogic( uint16_t logicNumber, const uint8_t *logicDefinitionBuffer, uint8_t bufferSize );

		void __REMOVE__check_written( uint16_t logicNumber );
	protected:
	    AxonLogicManager();							// constructor
};

#endif