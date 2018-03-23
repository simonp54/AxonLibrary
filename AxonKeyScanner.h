/* originally by Simon Peace
 * a wrapper for "key scanning" driver chip on the Axon
 * VERSION 1.0 28/02/2018
 */

#ifndef AXON_KEYSCANNER_h
#define AXON_KEYSCANNER_h

#include "Arduino.h"
#include "AxonAction.h"

class AxonKeyScanner
{
  public:
		static AxonKeyScanner *instance();
		
		void setOnKeyScan0( AxonAction *action )  { _onKeyScan[0] = action; }
		void setOnKeyScan1( AxonAction *action )  { _onKeyScan[1] = action; }
		void setOnKeyScan2( AxonAction *action )  { _onKeyScan[2] = action; }
		void setOnKeyScan3( AxonAction *action )  { _onKeyScan[3] = action; }
		void setOnKeyScan4( AxonAction *action )  { _onKeyScan[4] = action; }
		void setOnKeyScan5( AxonAction *action )  { _onKeyScan[5] = action; }
		void setOnKeyScan6( AxonAction *action )  { _onKeyScan[6] = action; }
		void setOnKeyScan7( AxonAction *action )  { _onKeyScan[7] = action; }
		void setOnKeyScan8( AxonAction *action )  { _onKeyScan[8] = action; }
		void setOnKeyScan9( AxonAction *action )  { _onKeyScan[9] = action; }
		void setOnKeyScan10( AxonAction *action ) { _onKeyScan[10] = action; }
		void setOnKeyScan11( AxonAction *action ) { _onKeyScan[11] = action; }
		void setOnKeyScan12( AxonAction *action ) { _onKeyScan[12] = action; }
		void setOnKeyScan13( AxonAction *action ) { _onKeyScan[13] = action; }
		void setOnKeyScan14( AxonAction *action ) { _onKeyScan[14] = action; }
		void setOnKeyScan15( AxonAction *action ) { _onKeyScan[15] = action; }
		void setOnKeyScan16( AxonAction *action ) { _onKeyScan[16] = action; }
		void setOnKeyScan17( AxonAction *action ) { _onKeyScan[17] = action; }
		void setOnKeyScan18( AxonAction *action ) { _onKeyScan[18] = action; }
		void setOnKeyScan19( AxonAction *action ) { _onKeyScan[19] = action; }
		void setOnKeyScan20( AxonAction *action ) { _onKeyScan[20] = action; }
		void setOnKeyScan21( AxonAction *action ) { _onKeyScan[21] = action; }
		void setOnKeyScan22( AxonAction *action ) { _onKeyScan[22] = action; }
		void setOnKeyScan23( AxonAction *action ) { _onKeyScan[23] = action; }
				
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
		
		AxonAction *_onKeyScan[_NUMBER_OF_ROWS * _NUMBER_OF_COLUMNS] = {0};
};

#endif