#ifndef AXON_ACTION_MANAGER_h
#define AXON_ACTION_MANAGER_h

#include "AxonEvent.h"
#include "Arduino.h"

class AxonActionManager
{
	private:
		static AxonActionManager *_instance;
		
		static const uint32_t _baseAddress = 0x30000;

		struct AxonActionInfoNoName_t
		{
			uint8_t actionCode;
			uint8_t param1;
			uint8_t param2;
			uint8_t param3;
			uint8_t param4;
		};
		
	public:
		static const uint16_t maxActionItems = 1016;
		static const uint8_t maxOverrideActionItems = 8;
		static const uint8_t actionNameSize = 20;

		static const uint8_t NO_ERROR;
		static const uint8_t INVALID_ACTION_SLOT;
		static const uint8_t UNABLE_TO_WRITE;
		static const uint8_t UNABLE_TO_READ;

		static AxonActionManager *instance();
		
		void format();
		
		struct AxonActionInfo_t: AxonActionInfoNoName_t
		{
			uint8_t name[actionNameSize];
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
		static const uint8_t AxonSendMidiCCActionCode                       = 1;
		static const uint8_t AxonSendMidiFixedCCActionCode					= 2;
		static const uint8_t AxonSendMidiPCActionCode                       = 3;

		static const uint8_t AxonContrastDownActionCode                     = 11;
		static const uint8_t AxonContrastSetActionCode                      = 12;
		static const uint8_t AxonContrastUpActionCode                       = 13;
		static const uint8_t AxonNextSurfaceActionCode						= 14;
		static const uint8_t AxonPreviousSurfaceActionCode					= 15;
/*		static const uint8_t AxonShowMainScreenActionCode                   = xxx;
		static const uint8_t AxonShowPresetNameActionCode                   = xxx;
		static const uint8_t AxonShowPresetNumberActionCode                 = xxx;
		static const uint8_t AxonShowSceneNumberActionCode                  = xxx;
		static const uint8_t AxonShowTunerScreenActionCode                  = xxx;

		static const uint8_t AxonAFXXLPPresetBlocksDataRequestActionCode    = xxx;
		static const uint8_t AxonAFXXLPPresetDownActionCode                 = xxx;
		static const uint8_t AxonAFXXLPPresetNameRequestActionCode          = xxx;
		static const uint8_t AxonAFXXLPPresetNumberRequestActionCode        = xxx;
		static const uint8_t AxonAFXXLPPresetUpActionCode                   = xxx;
		static const uint8_t AxonAFXXLPSceneNumberRequestActionCode         = xxx;
		static const uint8_t AxonAFXXLPSysExActionCode                      = xxx;
		static const uint8_t AxonAFXXLPTunerInfoActionCode                  = xxx;
		static const uint8_t AxonStoreAFXXLPPresetNameActionCode            = xxx;
		static const uint8_t AxonStoreAFXXLPPresetNumberActionCode          = xxx;
		static const uint8_t AxonStoreAFXXLPSceneNumberActionCode           = xxx;
*/
};

#endif