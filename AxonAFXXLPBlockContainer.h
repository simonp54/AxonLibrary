#ifndef AXONAXEFXXLPLUSBLOCKCONTAINER_h
#define AXONAXEFXXLPLUSBLOCKCONTAINER_h

#include "Arduino.h"

class AxonAFXXLPBlockContainer
{
	public:
		void setBypass( bool newState ) { _bypass = newState; }
		void setXYState( bool newState ) { _XYState = newState; }
		void setBlockID( uint8_t newID ) { _blockID = newID; }
		void setBypassCC( uint8_t newCC ) { _bypassCC = newCC; }
		void setXYCC( uint8_t newCC ) { _XYCC = newCC; }
		
		bool getBypass() { return _bypass; }		
		bool inStateX() { return _XYState == true; }
		bool inStateY() { return _XYState == false; }
		uint8_t getBlockID() { return _blockID; }
		uint8_t getbypassCC() { return _bypassCC; }
		uint8_t getXYCC() { return _XYCC; }
		
	private:
		bool _bypass = false;
		bool _XYState = false;
		uint8_t _blockID = 0xFF;
		uint8_t _bypassCC = 0xFF;
		uint8_t _XYCC = 0xFF;
};

#endif