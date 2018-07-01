#ifndef AXON_PRESET_MANAGER_h
#define AXON_PRESET_MANAGER_h

#include "Arduino.h"

class AxonPresetManager
{
	private:
		static AxonPresetManager *_instance;
		
		static const uint32_t _baseAddress = 0x047C00;
		
		uint16_t _qPresetNumber = 0;
		bool _presetQueued = false;

	public:
		static const uint8_t NO_ERROR;
		static const uint8_t INVALID_PRESET_NUMBER;
		static const uint8_t UNABLE_TO_WRITE;
		static const uint8_t UNABLE_TO_READ;

		static const uint16_t maxPresetItems = 1024;
		static const uint8_t actionSlotsPerPreset = 32;

		static AxonPresetManager *instance();
		
		bool itemOutstanding() { return( _presetQueued ); }
		void processOutstanding();
		
		void format();
		
		struct AxonPresetInfo_t
		{
			uint8_t surfaceNumber;
			uint16_t actionSlot[actionSlotsPerPreset];
		};
		
		uint8_t definePreset( uint16_t presetNumber, const AxonPresetInfo_t *presetInfo );
		uint8_t getPresetBuffer( uint16_t presetNumber, AxonPresetInfo_t *presetInfo );
		
		void qPreset( uint16_t presetNumber );
		
		void __REMOVE__check_written( uint16_t presetNumber );
	protected:
	    AxonPresetManager();							// constructor
		void loadPreset( uint16_t presetNumber );

};

#endif