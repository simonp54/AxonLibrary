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
		
		void onScene1Rxd( AxonAction *action ) { _onScene1Rxd = action; }
		void onScene2Rxd( AxonAction *action ) { _onScene2Rxd = action; }
		void onScene3Rxd( AxonAction *action ) { _onScene3Rxd = action; }
		void onScene4Rxd( AxonAction *action ) { _onScene4Rxd = action; }
		void onScene5Rxd( AxonAction *action ) { _onScene5Rxd = action; }
		void onScene6Rxd( AxonAction *action ) { _onScene6Rxd = action; }
		void onScene7Rxd( AxonAction *action ) { _onScene7Rxd = action; }
		void onScene8Rxd( AxonAction *action ) { _onScene8Rxd = action; }
	private:
		AxonAction *_onScene1Rxd = 0;
		AxonAction *_onScene2Rxd = 0;
		AxonAction *_onScene3Rxd = 0;
		AxonAction *_onScene4Rxd = 0;
		AxonAction *_onScene5Rxd = 0;
		AxonAction *_onScene6Rxd = 0;
		AxonAction *_onScene7Rxd = 0;
		AxonAction *_onScene8Rxd = 0;
};

#endif