#ifndef AXON_AXEFXXLPLUSPRESETNUMBERDECODER_h
#define AXON_AXEFXXLPLUSPRESETNUMBERDECODER_h

#include "AxonAxeFXXLPlusChecksumDecoder.h"
#include "AxonSysExMidiEvent.h"
#include "AxonAction.h"

class AxonAxeFXXLPlusPresetNumberDecoder: public AxonAxeFXXLPlusChecksumDecoder
{
	public:
		AxonAxeFXXLPlusPresetNumberDecoder();
		
		virtual bool decode( AxonSysExMidiEvent *event );
};

#endif