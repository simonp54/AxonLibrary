#ifndef AXONFASSCENENUMBEREVENT_h
#define AXONFASSCENENUMBEREVENT_h

#include "AxonAFXXLPEvent.h"
#include "AxonEvent.h"
#include "Arduino.h"

class AxonAFXXLPSceneNumberEvent: public AxonAFXXLPEvent
{
	public:
		AxonAFXXLPSceneNumberEvent( );
		
		void setSceneNumber( uint8_t scene );
		uint8_t getSceneNumber() { return _sceneNumber; }

		bool exactMatch( AxonEvent *event );
	protected:
	private:
		uint8_t _sceneNumber = 0;
};

#endif