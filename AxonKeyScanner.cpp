/* originally by Simon Peace
 * a wrapper for "keyscanner" driver chip on the Axon
 * VERSION 1.0 28/02/2018
 */

#include "AxonKeyScanner.h"
#include "AxonHardwareSwitchEvent.h"
#include "Wire.h"

#include "AxonDebugDefines.h"
#include "AxonCheckMem.h"



AxonKeyScanner *AxonKeyScanner::_instance = 0;

const uint8_t AxonKeyScanner::_SW_COLUMN_MASK[] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40,0x80 };

AxonKeyScanner *AxonKeyScanner::instance()
{
	if (!_instance)
	{
		_instance = new AxonKeyScanner();
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
	}
	return _instance;
}

/*
 *  CONSTRUCTOR FOR CLASS
 */
AxonKeyScanner::AxonKeyScanner()
{
	if (TWCR == 0) // do this check so that Wire only gets initialized once
	{
		Wire.begin();
	}
	
	for( uint8_t i = 0; i < _NUMBER_OF_ROWS; i++ )
	{
		_rowScan[i] = 0;
		_prev_rowScan[i] = 0;
	}
	
	_lastCheckMillis = millis();
}


void AxonKeyScanner::setOnKeyScan( uint8_t index, AxonLogicBlock *logicBlock )
{
	_onKeyScan[constrain( index, 0, _NUMBER_OF_ROWS * _NUMBER_OF_COLUMNS )] = logicBlock;
}


/*
 *  CALLED BY THE CLIENT TO SERVICE THE KEYBOARD (AS FREQUENTLY AS POSSIBLE)
 *  BUT internally limited to the fastest that seems stable (20ms)
 */
void AxonKeyScanner::check()
{
  if ( _lastCheckMillis + _QUICKEST_RECHECK_INTERVAL > millis() )
  {
	  return;			// do nothing... its too soon.
  }
  
  // READ SWITCH INPUTS - which are connected to KEYBOARD_CTRL
  Wire.beginTransmission( _KEYBOARD_CTRL_ADDR );
  Wire.write( _KEYSCAN_ZERO_COMMAND );    // read KS0 Keyboard Command
  Wire.endTransmission();
  Wire.requestFrom( _KEYBOARD_CTRL_ADDR, _BYTES_TO_RETURN );

  if (_BYTES_TO_RETURN <= Wire.available())
  {
    // only interested in the LSB of each of these as we only have 8 buttons on each row
    _rowScan[0] = Wire.read();  // COM01
    uint8_t ks01msb = Wire.read();  // COM01
    _rowScan[1] = Wire.read();  // COM02
    uint8_t ks02msb = Wire.read();  // COM02
    _rowScan[2] = Wire.read();  // COM03
    uint8_t ks03msb = Wire.read();  // COM03

	for( uint8_t i = 0; i < _NUMBER_OF_ROWS; i++ )					// run through each row
	{
		for( uint8_t j = 0; j < _NUMBER_OF_COLUMNS; j++ )			// run through each column
		{
			// if the scan is down... or it has changed... then notify
			// if the scan has changed since the last "service" for this SPECIFIC subject...
			if ( 	( (_rowScan[i] & _SW_COLUMN_MASK[j]) == _SW_COLUMN_MASK[j] ) ||
					  (_prev_rowScan[i] & _SW_COLUMN_MASK[j]) != (_rowScan[i] & _SW_COLUMN_MASK[j]) )
			{
				// notify the event occurred
				AxonHardwareSwitchEvent *event = new AxonHardwareSwitchEvent( (i*8)+j );
				event->setSwitchState( (_rowScan[i] & _SW_COLUMN_MASK[j]) == _SW_COLUMN_MASK[j] );
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
				if (_onKeyScan[(i*8)+j])
				{
					_onKeyScan[(i*8)+j]->execute( NULL, event );
				}

				delete event;
			}
		}
	}
	
	// copy across the values from current to "previous" for next service round
	_prev_rowScan[0] = _rowScan[0];
	_prev_rowScan[1] = _rowScan[1];
	_prev_rowScan[2] = _rowScan[2];
  }
  
  _lastCheckMillis = millis();			// store the "last time" we ran this service routine
}