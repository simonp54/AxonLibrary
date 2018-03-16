#ifndef AXON_AXEFXXLPLUSPRESETBLOCKSDATADECODER_h
#define AXON_AXEFXXLPLUSPRESETBLOCKSDATADECODER_h

#include "AxonSysExMidiEvent.h"
#include "AxonAxeFXXLPlusModelDecoder.h"

class AxonAxeFXXLPlusPresetBlocksDataDecoder: public AxonAxeFXXLPlusModelDecoder
{
	public:
		AxonAxeFXXLPlusPresetBlocksDataDecoder();
		
		virtual bool decode( AxonSysExMidiEvent *event );
	protected:

};

#endif