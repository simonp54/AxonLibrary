#ifndef AXON_AXEFXXLPLUSMODELDECODER_h
#define AXON_AXEFXXLPLUSMODELDECODER_h

#include "Arduino.h"
#include "AxonFASManufacturerDecoder.h"

class AxonAxeFXXLPlusModelDecoder: public AxonFASManufacturerDecoder
{
	public:
		AxonAxeFXXLPlusModelDecoder();
		
		virtual bool decode( AxonSysExMidiEvent *event );
	protected:

};

#endif