#ifndef AXON_DECODER_h
#define AXON_DECODER_h

#include "AxonSysExMidiEvent.h"
#include "AxonAction.h"
#include "Arduino.h"


class AxonDecoder
{
	public:
		AxonDecoder();
		virtual ~AxonDecoder() {};
		virtual void onSuccess( AxonAction *action ) { _onSuccess = action; }
		
		uint16_t getGroupID() { return _groupID; }
		
		bool sameType( AxonDecoder *decoder );
		
		virtual bool decode( AxonSysExMidiEvent *event ) = 0;
	protected:
		uint16_t _groupID;
		
		AxonAction *_onSuccess = 0;
	private:
};

#endif
