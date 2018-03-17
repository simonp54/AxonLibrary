#ifndef AXON_SWITCHEVENT_h
#define AXON_SWITCHEVENT_h

#include "Arduino.h"
#include "AxonEvent.h"

class AxonSwitchEvent: public AxonEvent
{
	public:
		AxonSwitchEvent( uint8_t switchNumber );

		uint8_t getSwitchNumber() { return _switchNumber; }
		bool getSwitchState() { return (_val > ((_valMax - _valMin)>>1)); }
		void setSwitchState( bool newstate ) { newstate ? _val = SWITCH_MAX_VALUE : _val = SWITCH_MIN_VALUE; }
		
		uint8_t getVal() { return min( map( _val, SWITCH_MIN_VALUE, SWITCH_MAX_VALUE, _valMin, _valMax), SWITCH_MAX_VALUE ); }
		void setVal( uint8_t val ) { _val = (val & SWITCH_MAX_VALUE); }
		
		
		uint8_t getMax() { return _valMax; }
		void setMax( uint8_t max ) { _valMax = (max & SWITCH_MAX_VALUE); }
		uint8_t getMin() { return _valMin; }
		void setMin( uint8_t min ) { _valMin = (min & SWITCH_MAX_VALUE); }

		bool exactMatch( AxonEvent *event );
	protected:
		uint8_t _switchNumber;
		uint8_t _val = SWITCH_MIN_VALUE;
		
		uint8_t _valMin = SWITCH_MIN_VALUE;
		uint8_t _valMax = SWITCH_MAX_VALUE;
		
		static const uint8_t SWITCH_MIN_VALUE = 0x00;
		static const uint8_t SWITCH_MAX_VALUE = 0x7F;
};

#endif