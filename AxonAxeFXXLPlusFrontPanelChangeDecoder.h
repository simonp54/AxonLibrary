#ifndef AXON_AXEFXXLPLUSFRONTPANELCHANGEDECODER_h
#define AXON_AXEFXXLPLUSFRONTPANELCHANGEDECODER_h

#include "Arduino.h"
#include "AxonAxeFXXLPlusChecksumDecoder.h"
#include "AxonAction.h"

class AxonAxeFXXLPlusFrontPanelChangeDecoder: public AxonAxeFXXLPlusChecksumDecoder
{
	public:
		AxonAxeFXXLPlusFrontPanelChangeDecoder();
		
		virtual bool decode( AxonSysExMidiEvent *event );
};

#endif