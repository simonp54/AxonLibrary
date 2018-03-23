#ifndef AXON_AXEFXXLPLUSSCENENUMBERDECODER_h
#define AXON_AXEFXXLPLUSSCENENUMBERDECODER_h

#include "AxonAFXXLPChecksumDecoder.h"
#include "AxonSysExMidiEvent.h"
#include "AxonAction.h"

class AxonAFXXLPSceneNumberDecoder: public AxonAFXXLPChecksumDecoder
{
	public:
		AxonAFXXLPSceneNumberDecoder();
		
		virtual bool decode( AxonSysExMidiEvent *event );
		
		void onSceneRxd( AxonAction *action ) { _onSceneRxd = action; }
	private:
		AxonAction *_onSceneRxd = 0;
};

#endif