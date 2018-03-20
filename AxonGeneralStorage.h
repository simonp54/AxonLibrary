/* originally by Simon Peace
 * an object to provide "general storage" access in a controlled manner
 * VERSION 1.0 11/03/2018
 */

#ifndef AXON_GENERAL_STORAGE_h
#define AXON_GENERAL_STORAGE_h

#include "AxonStorage.h"


class AxonGeneralStorage
{
  public:
		static AxonGeneralStorage *instance();
//		void FORMAT();
		
		uint16_t readAFXXLPPresetNumber();
		void writeAFXXLPPresetNumber( uint16_t tmp );
		
		uint8_t readAFXSceneNumber();
		void writeAFXSceneNumber( uint8_t tmp );
		
		const char *readAFXXLPPresetName();
		void writeAFXXLPPresetName( const char *name );

		uint8_t readTouchScreenContrast();
		void writeTouchScreenContrast( uint8_t tmp );
		
		static const uint8_t AXEFX_PRESET_NAME_MAXIMUM_SIZE = 32;				// without the null
	protected:
	    AxonGeneralStorage();							// constructor
	private:
		static AxonGeneralStorage *_instance;
		
		AxonStorage *_AS;
	
		static const uint32_t _ADDRESS_SPACE_START = 0x060000;
		static const uint32_t _ADDRESS_SPACE_END = 0x07FFFF;
		
		static const uint32_t TOUCH_SCREEN_CONTRAST_ADDR	= 0x060000;			// 1 byte
		static const uint32_t AXEFX_PRESET_NUMBER_ADDR		= 0x060001;			// 2 bytes
		static const uint32_t AXEFX_SCENE_NUMBER_ADDR		= 0x060003;			// 1 byte
		static const uint32_t AXEFX_PRESET_NAME_ADDR		= 0x060004;			// 32 bytes
		static const uint32_t ____NEXTAVAILABLEADDR____		= 0x060024;			// ?? bytes
		
};

#endif