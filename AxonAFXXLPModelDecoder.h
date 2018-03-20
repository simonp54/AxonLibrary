#ifndef AXON_AXEFXXLPLUSMODELDECODER_h
#define AXON_AXEFXXLPLUSMODELDECODER_h

#include "Arduino.h"
#include "AxonFASManufacturerDecoder.h"

class AxonAFXXLPModelDecoder: public AxonFASManufacturerDecoder
{
	public:
		AxonAFXXLPModelDecoder();
		
		virtual bool decode( AxonSysExMidiEvent *event );
	protected:

};

#endif