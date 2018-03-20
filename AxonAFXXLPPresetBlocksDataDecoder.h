#ifndef AXON_AXEFXXLPLUSPRESETBLOCKSDATADECODER_h
#define AXON_AXEFXXLPLUSPRESETBLOCKSDATADECODER_h

#include "AxonSysExMidiEvent.h"
#include "AxonAFXXLPModelDecoder.h"

class AxonAFXXLPPresetBlocksDataDecoder: public AxonAFXXLPModelDecoder
{
	public:
		AxonAFXXLPPresetBlocksDataDecoder();
		
		virtual bool decode( AxonSysExMidiEvent *event );
	protected:

};

#endif