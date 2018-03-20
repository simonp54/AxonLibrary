/* originally by Simon Peace
 * a wrapper for "keyboard" driver chip on the Axon
 * implements as a "subject" so that "observers" can register for when updates happen
 * VERSION 1.0 15/02/2018
 */

#include "Arduino.h"
#include "AxonExprScanner.h"
#include "AxonEventManager.h"
#include "AxonHardwareSwitchEvent.h"

#include "AxonDebugDefines.h"
#include "AxonCheckMem.h"


AxonExprScanner *AxonExprScanner::_instance = 0;
AnalogPin *AxonExprScanner::_EXPR_pedal[];

const uint8_t AxonExprScanner::_EXPRESSION_PINS[] = { A0, A1, A2, A3 };


AxonExprScanner *AxonExprScanner::instance()
{
	if (!_instance)
	{
		_instance = new AxonExprScanner();
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
	}
	return _instance;
}

/*
 *  CONSTRUCTOR FOR CLASS
 */
AxonExprScanner::AxonExprScanner()
{
	for( uint8_t i = 0; i < _NUMBER_OF_EXPR_PEDALS; i++ )
	{
		_prev_value[i] = 0;
		_curr_value[i] = 0;

		_EXPR_pedal[i] = new AnalogPin(_EXPRESSION_PINS[i]);
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
	}
	
	_lastCheckMillis = millis();
}


/*
 *  CALLED BY THE CLIENT TO SERVICE THE EXPRESSION PEDALS (AS FREQUENTLY AS POSSIBLE)
 *  BUT internally limited to the fastest that seems stable
 */
void AxonExprScanner::check()
{
	if ( _lastCheckMillis + _QUICKEST_RECHECK_INTERVAL > millis() )
	{
		return;			// do nothing... its too soon.
	}

	for( uint8_t i = 0; i < _NUMBER_OF_EXPR_PEDALS; i++ )					// run through each pin input
	{
		_curr_value[i] = min( map( _EXPR_pedal[i]->read(10), _URGH_CALIB_MIN, _URGH_CALIB_MAX, _URGH_SLIDER_MIN, _URGH_SLIDER_MAX ), _URGH_SLIDER_MAX );    //debounced analog read
		
		// if the scan has changed... then add to queue
		if ( (_prev_value[i] != _curr_value[i] ) )
		{
			// notify the event occurred
			AxonHardwareSwitchEvent *event = new AxonHardwareSwitchEvent( i+30 );
			event->setVal( _curr_value[i] );
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
			AxonEventManager::instance()->addToQueue( event );
		}
		// copy across the values from current to "previous" for next service round
		_prev_value[i] = _curr_value[i];
	}

	_lastCheckMillis = millis();			// store the "last time" we ran this service routine
}