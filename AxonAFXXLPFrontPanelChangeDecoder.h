#ifndef AXON_AXEFXXLPLUSFRONTPANELCHANGEDECODER_h
#define AXON_AXEFXXLPLUSFRONTPANELCHANGEDECODER_h

#include "Arduino.h"
#include "AxonAFXXLPChecksumDecoder.h"
#include "AxonAction.h"

class AxonAFXXLPFrontPanelChangeDecoder: public AxonAFXXLPChecksumDecoder
{
	public:
		AxonAFXXLPFrontPanelChangeDecoder();
		
		virtual bool decode( AxonSysExMidiEvent *event );
};

#endif