#ifndef AXON_LOGIC_MANAGER_h
#define AXON_LOGIC_MANAGER_h

#include "AxonLogicBlock.h"

#include "Arduino.h"

class AxonLogicManager
{
	private:
		static AxonLogicManager *_instance;
		
		static const uint32_t _baseAddress = 0x36400;
		static const uint16_t _maxLogicItems = 1024;
		
	public:
		static const uint8_t NO_ERROR;
		static const uint8_t INVALID_LOGIC_NUMBER;
		static const uint8_t UNABLE_TO_WRITE;
		static const uint8_t UNABLE_TO_READ;
		
		static const uint8_t actionSlotsPerLogicBlock = 32;

		static const uint8_t AxonMomentarySwitchLogicBlock_t                 = 1;
		static const uint8_t AxonLatchingSwitchLogicBlock_t                  = 2;
		static const uint8_t AxonVariableSwitchLogicBlock_t					 = 3;
//		static const uint8_t AxonRadioSwitchLogicBlock_t                     = 4;
//		static const uint8_t AxonRadioSwitchGroupLogicBlock_t                = 5;

		static AxonLogicManager *instance();
		
		void format();
		
		struct AxonLogicInfo_t
		{
			uint8_t logicCode;
			uint16_t actionSlot[actionSlotsPerLogicBlock];
		};
		
		uint8_t defineLogic( uint16_t logicNumber, const AxonLogicInfo_t *logicInfo );
		uint8_t getLogicBuffer( uint16_t logicNumber, AxonLogicInfo_t *logicInfo );
		
		AxonLogicBlock *createLogic( uint16_t logicNumber );

		void __REMOVE__check_written( uint16_t logicNumber );
	protected:
	    AxonLogicManager();							// constructor
};

#endif