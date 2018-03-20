/* originally by Simon Peace
 * Base AxonAction Class
 * VERSION 1.0 19/02/2018
 */
#ifndef AXON_CONTRAST_TYPE_h
#define AXON_CONTRAST_TYPE_h

#include "Arduino.h"
#include "AxonGeneralStorage.h"

class AxonContrastType
{
	public:
		uint8_t get()  { load(); return _contrast; }
//		void set( uint8_t contrast ) { _contrast = contrast & 0x0F; }
		
		uint8_t up()   { load(); _contrast=((_contrast+1) & 0x0F); save(); return _contrast; }
		uint8_t down() { load(); _contrast=((_contrast-1) & 0x0F); save(); return _contrast; }
	protected:	
		void load() { _contrast = AxonGeneralStorage::instance()->readTouchScreenContrast(); }
		void save() { AxonGeneralStorage::instance()->writeTouchScreenContrast( _contrast ); }
	private:
		uint8_t _contrast = 7;
};

#endif