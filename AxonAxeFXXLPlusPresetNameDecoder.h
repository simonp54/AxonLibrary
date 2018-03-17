#ifndef AXON_AXEFXXLPLUSPRESETNAMEDECODER_h
#define AXON_AXEFXXLPLUSPRESETNAMEDECODER_h

#include "AxonAxeFXXLPlusChecksumDecoder.h"
#include "AxonSysExMidiEvent.h"
#include "AxonAction.h"

class AxonAxeFXXLPlusPresetNameDecoder: public AxonAxeFXXLPlusChecksumDecoder
{
	public:
		AxonAxeFXXLPlusPresetNameDecoder();
		
		virtual bool decode( AxonSysExMidiEvent *event );
};

#endif