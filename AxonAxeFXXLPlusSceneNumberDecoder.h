#ifndef AXON_AXEFXXLPLUSSCENENUMBERDECODER_h
#define AXON_AXEFXXLPLUSSCENENUMBERDECODER_h

#include "AxonAxeFXXLPlusChecksumDecoder.h"
#include "AxonSysExMidiEvent.h"
#include "AxonAction.h"

class AxonAxeFXXLPlusSceneNumberDecoder: public AxonAxeFXXLPlusChecksumDecoder
{
	public:
		AxonAxeFXXLPlusSceneNumberDecoder();
		
		virtual bool decode( AxonSysExMidiEvent *event );
};

#endif