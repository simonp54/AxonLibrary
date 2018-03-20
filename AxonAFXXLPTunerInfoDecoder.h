#ifndef AXON_AXEFXXLPLUSTUNERINFODECODER_h
#define AXON_AXEFXXLPLUSTUNERINFODECODER_h

#include "Arduino.h"
#include "AxonAFXXLPModelDecoder.h"

class AxonAFXXLPTunerInfoDecoder: public AxonAFXXLPModelDecoder
{
	public:
		AxonAFXXLPTunerInfoDecoder();
		
		virtual bool decode( AxonSysExMidiEvent *event );
	protected:

};

#endif