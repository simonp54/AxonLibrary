#ifndef AXON_AXEFXXLPLUSTUNERINFODECODER_h
#define AXON_AXEFXXLPLUSTUNERINFODECODER_h

#include "Arduino.h"
#include "AxonAxeFXXLPlusModelDecoder.h"

class AxonAxeFXXLPlusTunerInfoDecoder: public AxonAxeFXXLPlusModelDecoder
{
	public:
		AxonAxeFXXLPlusTunerInfoDecoder();
		
		virtual bool decode( AxonSysExMidiEvent *event );
	protected:

};

#endif