#ifndef AXON_DECODER_h
#define AXON_DECODER_h

#include "AxonSysExMidiEvent.h"
#include "Arduino.h"


class AxonDecoder
{
	public:
		AxonDecoder();
		virtual ~AxonDecoder() {};
		
		uint16_t getGroupID() { return _groupID; }
		
		bool sameType( AxonDecoder *decoder );
		
		virtual bool decode( AxonSysExMidiEvent *event ) = 0;
	protected:
		uint16_t _groupID;
	private:
};

#endif
