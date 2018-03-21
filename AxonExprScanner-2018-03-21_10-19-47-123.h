/* originally by Simon Peace
 * a wrapper for "expression inputs" on the Axon
 * a singleton class
 * VERSION 1.0 21/02/2018
 */

#ifndef AXON_EXPRSCANNER_h
#define AXON_EXPRSCANNER_h

#include "AxonAction.h"
#include "AnalogPin.h"

#define _URGH_CALIB_MIN 0
#define _URGH_CALIB_MAX 937
#define _URGH_SLIDER_MIN 0
#define _URGH_SLIDER_MAX 127

class AxonExprScanner
{
  public:
		static AxonExprScanner *instance();
		
		void setOnExpr1Change( AxonAction *action ) { _onExprChange[0] = action; }
		void setOnExpr2Change( AxonAction *action ) { _onExprChange[1] = action; }
		void setOnExpr3Change( AxonAction *action ) { _onExprChange[2] = action; }
		void setOnExpr4Change( AxonAction *action ) { _onExprChange[3] = action; }

		static const uint8_t _NUMBER_OF_EXPR_PEDALS = 4;
				
		void check();													// the servicing routine that needs to be called every time through a program loop
	protected:
	    AxonExprScanner();												// constructor
	private:
		static AxonExprScanner *_instance;
		
		static AnalogPin *_EXPR_pedal[_NUMBER_OF_EXPR_PEDALS];
	
		static const uint8_t _EXPRESSION_PINS[_NUMBER_OF_EXPR_PEDALS];
		static const uint8_t _QUICKEST_RECHECK_INTERVAL = 1;
		
		uint8_t _prev_value[_NUMBER_OF_EXPR_PEDALS];					// the "previous scan state"
		uint8_t _curr_value[_NUMBER_OF_EXPR_PEDALS];					// the "current scan state"
		
		uint64_t _lastCheckMillis;										// throttle timing
		
		AxonAction *_onExpr1Change[_NUMBER_OF_EXPR_PEDALS] = 0;
};

#endif