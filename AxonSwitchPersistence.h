#ifndef AXON_SWITCH_PERSISTENCE_h
#define AXON_SWITCH_PERSISTENCE_h

#include "AxonAction.h"
#include "AxonMultiOnOffChangeAction.h"
#include "Arduino.h"

class AxonSwitchPersistence
{
  public:
	    AxonSwitchPersistence();							// constructor
		uint32_t getSize();
		
		void setBaseAddress( uint32_t baseAddress );

		void format();
		
		void defineLogic( uint8_t logicType );
		void defineAction( uint8_t type, uint8_t param1 = 0x00, uint8_t param2 = 0x00, uint8_t param3 = 0x00, uint8_t param4 = 0x00 );
		
		void build();
		
		AxonMultiOnOffChangeAction *logic() { return _logic; }
		
		static const uint8_t AxonSwitchPersistence::AxonContrastDownAction_t                        = 0x01;
		static const uint8_t AxonSwitchPersistence::AxonContrastSetAction_t                         = 0x02;
		static const uint8_t AxonSwitchPersistence::AxonContrastUpAction_t                          = 0x03;
		static const uint8_t AxonSwitchPersistence::AxonLabelDisplayAction_t                        = 0x04;
		static const uint8_t AxonSwitchPersistence::AxonLatchingSwitchAction_t                      = 0x05;
		static const uint8_t AxonSwitchPersistence::AxonMacroAction_t                               = 0x06;
		static const uint8_t AxonSwitchPersistence::AxonMomentarySwitchAction_t                     = 0x07;
		static const uint8_t AxonSwitchPersistence::AxonRadioSwitchAction_t                         = 0x08;
		static const uint8_t AxonSwitchPersistence::AxonRadioSwitchGroupAction_t                    = 0x09;
		static const uint8_t AxonSwitchPersistence::AxonShowMainScreenAction_t                      = 0x0A;
		static const uint8_t AxonSwitchPersistence::AxonU2BabyMemoryMapAction_t                     = 0x0B;

		static const uint8_t AxonSwitchPersistence::AxonSendMidiCCAction_t                          = 0x0D;
		static const uint8_t AxonSwitchPersistence::AxonSendMidiFixedCCAction_t						= 0x0E;
		static const uint8_t AxonSwitchPersistence::AxonSendMidiPCAction_t                          = 0x0F;

		static const uint8_t AxonSwitchPersistence::AxonAFXXLPPresetBlocksDataRequestAction_t       = 0x11;
		static const uint8_t AxonSwitchPersistence::AxonAFXXLPPresetDownAction_t                    = 0x12;
		static const uint8_t AxonSwitchPersistence::AxonAFXXLPPresetNameRequestAction_t             = 0x13;
		static const uint8_t AxonSwitchPersistence::AxonAFXXLPPresetNumberRequestAction_t           = 0x14;
		static const uint8_t AxonSwitchPersistence::AxonAFXXLPPresetUpAction_t                      = 0x15;
		static const uint8_t AxonSwitchPersistence::AxonAFXXLPSceneNumberRequestAction_t            = 0x16;
		static const uint8_t AxonSwitchPersistence::AxonAFXXLPSysExAction_t                         = 0x17;
		static const uint8_t AxonSwitchPersistence::AxonAFXXLPTunerInfoAction_t                     = 0x18;
		static const uint8_t AxonSwitchPersistence::AxonShowPresetNameAction_t                      = 0x19;
		static const uint8_t AxonSwitchPersistence::AxonShowPresetNumberAction_t                    = 0x1A;
		static const uint8_t AxonSwitchPersistence::AxonShowSceneNumberAction_t                     = 0x1B;
		static const uint8_t AxonSwitchPersistence::AxonShowTunerScreenAction_t                     = 0x1C;
		static const uint8_t AxonSwitchPersistence::AxonStoreAFXXLPPresetNameAction_t               = 0x1D;
		static const uint8_t AxonSwitchPersistence::AxonStoreAFXXLPPresetNumberAction_t             = 0x1E;
		static const uint8_t AxonSwitchPersistence::AxonStoreAFXXLPSceneNumberAction_t              = 0x1F;
		
		static const uint8_t AxonOnActionHook_t = 0x80;
		static const uint8_t AxonOffActionHook_t = 0x40;
		static const uint8_t AxonChangeActionHook_t = 0x20;
		

	protected:
	private:
		static const uint8_t _hookMask = 0xE0;
		static const uint8_t _actionMask = 0x1F;

		bool _contextOK = false;
		
		bool buildLogic();
		bool buildActions();
	
		static const uint8_t _maxActionsPerSwitch = 8;				// one more for the display


		uint8_t _logicType;								// this holds the ID of the switch type

		struct _aMap_t
		{
			uint8_t type;
			uint8_t param1;
			uint8_t param2;
			uint8_t param3;
			uint8_t param4;
		} _actionMap;
		
		static const uint8_t _size = sizeof( _logicType ) + (sizeof( _actionMap ) * _maxActionsPerSwitch);
		
		uint32_t _baseAddress;
		
		AxonMultiOnOffChangeAction *_logic = 0;
		AxonAction *_actionList[_maxActionsPerSwitch] = { 0 };
		uint8_t _actionCount = 0;
};

#endif