#ifndef AXONFASTUNERINFOEVENT_h
#define AXONFASTUNERINFOEVENT_h

#include "AxonAFXXLPEvent.h"
#include "AxonEvent.h"
#include "Arduino.h"

class AxonAFXXLPTunerInfoEvent: public AxonAFXXLPEvent
{
	public:
		AxonAFXXLPTunerInfoEvent( );
		
		void setNote( uint8_t note ) { _note = note; }
		uint8_t getNote() { return _note; }
		void setString( uint8_t string ) { _string = string; }
		uint8_t getString() { return _string; }
		void setData( uint8_t data ) { _data = data; }
		uint8_t getData() { return _data; }

		bool exactMatch( AxonEvent *event );
	protected:
	private:
		uint8_t _note;
		uint8_t _string;
		uint8_t _data;
};

#endif