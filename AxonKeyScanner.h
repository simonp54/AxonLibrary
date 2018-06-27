/* originally by Simon Peace
 * a wrapper for "key scanning" driver chip on the Axon
 * VERSION 1.0 28/02/2018
 */

#ifndef AXON_KEYSCANNER_h
#define AXON_KEYSCANNER_h

#include "Arduino.h"
#include "AxonLogicBlock.h"

class AxonKeyScanner
{
  public:
		static AxonKeyScanner *instance();
		
		void setOnKeyScan( uint8_t index, AxonLogicBlock *logicBlock );
				
		void check();							// the servicing routine that needs to be called every time through a program loop
	protected:
	    AxonKeyScanner();							// constructor
	private:
		static AxonKeyScanner *_instance;
	
		static const uint8_t _KEYBOARD_CTRL_ADDR = 0x70;		// internal parameters
		static const uint8_t _KEYSCAN_ZERO_COMMAND = 0x40;
		static const uint8_t _BYTES_TO_RETURN = 6;
		static const uint8_t _NUMBER_OF_ROWS = 3;
		static const uint8_t _NUMBER_OF_COLUMNS = 8;
		static const uint8_t _QUICKEST_RECHECK_INTERVAL = 20;
		static const uint8_t _SW_COLUMN_MASK[];
		
		uint8_t _prev_rowScan[_NUMBER_OF_ROWS];					// the "previous scan state" of ALL the buttons
		uint8_t _rowScan[_NUMBER_OF_ROWS];						// the "current scan state" of ALL the buttons
		
		uint64_t _lastCheckMillis;								// throttle timing
		
		AxonLogicBlock *_onKeyScan[_NUMBER_OF_ROWS * _NUMBER_OF_COLUMNS] = {0};
};

#endif