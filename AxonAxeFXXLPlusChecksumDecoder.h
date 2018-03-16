#ifndef AXON_AXEFXXLPLUSCHECKSUMDECODER_h
#define AXON_AXEFXXLPLUSCHECKSUMDECODER_h

#include "Arduino.h"
#include "AxonAxeFXXLPlusModelDecoder.h"

class AxonAxeFXXLPlusChecksumDecoder: public AxonAxeFXXLPlusModelDecoder
{
	public:
		AxonAxeFXXLPlusChecksumDecoder();
		
		virtual bool decode( AxonSysExMidiEvent *event );
	protected:
	private:
		uint8_t calcChecksum( AxonSysExMidiEvent *event );
};

#endif