#ifndef AXONFASPRESETNUMBEREVENT_h
#define AXONFASPRESETNUMBEREVENT_h

#include "AxonFASEvent.h"
#include "AxonEvent.h"
#include "Arduino.h"

class AxonFASPresetNumberEvent: public AxonFASEvent
{
	public:
		AxonFASPresetNumberEvent( );
		
		void setPresetNumber( uint8_t msByte, uint8_t lsByte );
		uint16_t getPresetNumber() { return _presetNumber; }

		bool exactMatch( AxonEvent *event );
	protected:
	private:
		uint16_t _presetNumber = 0;
};

#endif