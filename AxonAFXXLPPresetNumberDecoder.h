#ifndef AXON_AXEFXXLPLUSPRESETNUMBERDECODER_h
#define AXON_AXEFXXLPLUSPRESETNUMBERDECODER_h

#include "AxonAFXXLPChecksumDecoder.h"
#include "AxonSysExMidiEvent.h"
#include "AxonAction.h"

class AxonAFXXLPPresetNumberDecoder: public AxonAFXXLPChecksumDecoder
{
	public:
		AxonAFXXLPPresetNumberDecoder();
		
		virtual bool decode( AxonSysExMidiEvent *event );
};

#endif