#ifndef AXON_AXEFXXLPLUSCHECKSUMDECODER_h
#define AXON_AXEFXXLPLUSCHECKSUMDECODER_h

#include "Arduino.h"
#include "AxonAFXXLPModelDecoder.h"

class AxonAFXXLPChecksumDecoder: public AxonAFXXLPModelDecoder
{
	public:
		AxonAFXXLPChecksumDecoder();
		
		virtual bool decode( AxonSysExMidiEvent *event );
	protected:
	private:
		uint8_t calcChecksum( AxonSysExMidiEvent *event );
};

#endif