#ifndef AXON_ACTION_MANAGER_h
#define AXON_ACTION_MANAGER_h

#include "AxonEvent.h"
#include "Arduino.h"

class AxonActionManager
{
	private:
		static AxonActionManager *_instance;
		
		static const uint32_t _baseAddress = 0x30000;
		static const uint16_t _maxActionItems = 1016;
		static const uint8_t _maxOverrideItems = 8;
		static const uint8_t _smallActionItemSize = 5;


		struct AxonActionInfoNoName_t
		{
			uint8_t actionCode;
			uint8_t param1;
			uint8_t param2;
			uint8_t param3;
			uint8_t param4;
		};
		
	public:
		static const uint8_t NO_ERROR;
		static const uint8_t INVALID_ACTION_SLOT;
		static const uint8_t UNABLE_TO_WRITE;
		static const uint8_t UNABLE_TO_READ;

		static AxonActionManager *instance();
		
		void format();
		
		struct AxonActionInfo_t: AxonActionInfoNoName_t
		{
			uint8_t name[20];
		};

		
		uint8_t defineAction( uint16_t actionSlot, const AxonActionInfo_t *actionInfo );
		uint8_t defineOverrideAction( uint16_t overrideSlot, const AxonActionInfo_t *actionInfo );
		uint8_t getActionInfo( uint16_t actionSlot, AxonActionInfo_t *actionInfo );
		uint8_t getShortActionInfo( uint16_t actionSlot, AxonActionInfoNoName_t *actionInfo );
		
		void executeAction( uint16_t actionSlot, AxonEvent *event );
		
		void __REMOVE__check_written( uint16_t actionSlot );

	private:
		uint8_t writeAction( uint16_t actionSlot, const AxonActionInfo_t *actionInfo );
	
	protected:
	    AxonActionManager();							// constructor
		
		
	public:
		static const uint8_t AxonSendMidiCCAction_t                          = 1;
		static const uint8_t AxonSendMidiFixedCCAction_t					 = 2;
		static const uint8_t AxonSendMidiPCAction_t                          = 3;

		static const uint8_t AxonContrastDownAction_t                        = 11;
		static const uint8_t AxonContrastSetAction_t                         = 12;
		static const uint8_t AxonContrastUpAction_t                          = 13;
/*		static const uint8_t AxonShowMainScreenAction_t                      = 14;
		static const uint8_t AxonShowPresetNameAction_t                      = 15;
		static const uint8_t AxonShowPresetNumberAction_t                    = 16;
		static const uint8_t AxonShowSceneNumberAction_t                     = 17;
		static const uint8_t AxonShowTunerScreenAction_t                     = 18;

		static const uint8_t AxonAFXXLPPresetBlocksDataRequestAction_t       = 21;
		static const uint8_t AxonAFXXLPPresetDownAction_t                    = 22;
		static const uint8_t AxonAFXXLPPresetNameRequestAction_t             = 23;
		static const uint8_t AxonAFXXLPPresetNumberRequestAction_t           = 24;
		static const uint8_t AxonAFXXLPPresetUpAction_t                      = 25;
		static const uint8_t AxonAFXXLPSceneNumberRequestAction_t            = 26;
		static const uint8_t AxonAFXXLPSysExAction_t                         = 27;
		static const uint8_t AxonAFXXLPTunerInfoAction_t                     = 28;
		static const uint8_t AxonStoreAFXXLPPresetNameAction_t               = 29;
		static const uint8_t AxonStoreAFXXLPPresetNumberAction_t             = 30;
		static const uint8_t AxonStoreAFXXLPSceneNumberAction_t              = 31;
*/
};

#endif