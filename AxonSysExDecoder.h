#ifndef AXON_SYSEXDECODER_h
#define AXON_SYSEXDECODER_h

#include "Arduino.h"
#include "AxonDecoder.h"

class AxonSysExDecoder: public AxonDecoder
{
	public:
		AxonSysExDecoder();
		
		virtual bool decode( AxonSysExMidiEvent *event );
	protected:

};

#endif