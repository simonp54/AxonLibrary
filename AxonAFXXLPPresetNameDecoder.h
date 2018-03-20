#ifndef AXON_AXEFXXLPLUSPRESETNAMEDECODER_h
#define AXON_AXEFXXLPLUSPRESETNAMEDECODER_h

#include "AxonAFXXLPChecksumDecoder.h"
#include "AxonSysExMidiEvent.h"
#include "AxonAction.h"

class AxonAFXXLPPresetNameDecoder: public AxonAFXXLPChecksumDecoder
{
	public:
		AxonAFXXLPPresetNameDecoder();
		
		virtual bool decode( AxonSysExMidiEvent *event );
};

#endif