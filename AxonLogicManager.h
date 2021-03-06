#ifndef AXON_LOGIC_MANAGER_h
#define AXON_LOGIC_MANAGER_h

#include "AxonLogicBlock.h"
#include "AxonDisplayBlock.h"

#include "Arduino.h"

class AxonLogicManager
{
	private:
		static AxonLogicManager *_instance;
		
		static const uint32_t _baseAddress = 0x36400;
		
	public:
		static const uint16_t maxLogicItems = 1024;

		static const uint8_t NO_ERROR;
		static const uint8_t INVALID_LOGIC_NUMBER;
		static const uint8_t UNABLE_TO_WRITE;
		static const uint8_t UNABLE_TO_READ;
		
		static const uint8_t actionSlotsPerLogicBlock = 32;

		static AxonLogicManager *instance();
		
		void format();
		
		struct AxonLogicInfo_t
		{
			uint8_t logicCode;
			uint8_t displayCode;
			uint8_t param1;
			uint8_t param2;
			uint8_t param3;
			uint8_t param4;
			uint16_t actionSlot[actionSlotsPerLogicBlock];
		};
		
		uint8_t defineLogic( uint16_t logicSlot, const AxonLogicInfo_t *logicInfo );
		uint8_t getLogicBuffer( uint16_t logicSlot, AxonLogicInfo_t *logicInfo );
		
		AxonLogicBlock *createLogic( uint16_t logicSlot, uint8_t scribbleID );

		void __REMOVE__check_written( uint16_t logicSlot );
	protected:
	    AxonLogicManager();							// constructor

	public:
		static const uint8_t AxonMomentarySwitchLogicBlockCode               = 1;
		static const uint8_t AxonLatchingSwitchLogicBlockCode                = 2;
		static const uint8_t AxonVariableSwitchLogicBlockCode				 = 3;
//		static const uint8_t AxonRadioSwitchLogicBlockCode                   = xxx;
//		static const uint8_t AxonRadioSwitchGroupLogicBlockCode              = xxx;

		static const uint8_t AxonLabelDisplayBlockCode						 = 1;
};

#endif