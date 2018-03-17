#include "AxonAxeFXSysExEventClient.h"
#include "AxonSysExMidiEvent.h"
#include "AxonAxeFXXLPlusTunerInfoDecoder.h"
#include "AxonAxeFXXLPlusFrontPanelChangeDecoder.h"
#include "AxonAxeFXXLPlusPresetBlocksDataDecoder.h"
#include "AxonAxeFXXLPlusPresetNumberDecoder.h"
#include "AxonAxeFXXLPlusPresetNameDecoder.h"
#include "AxonAxeFXXLPlusSceneNumberDecoder.h"
#include "AxonEvent.h"

#include "AxonDebugDefines.h"

void AxonAxeFXSysExEventClient::event( AxonEvent *event )
{
#ifdef DEBUG_AXON_AXE_FX_SYSEX_EVENT_CLIENT
	Serial.print( F("AxonAxeFXSysExEventClient::event         received:") );
	Serial.println( event->getGroupID(), BIN );
#endif
	AxonSysExMidiEvent *tmp = new AxonSysExMidiEvent();

	if (event->sameType(tmp))
	{
		AxonSysExMidiEvent *tmp2 = event;

		AxonAxeFXXLPlusTunerInfoDecoder *AxeFXXLPlusTunerInfoDecoder = new AxonAxeFXXLPlusTunerInfoDecoder();
		if ( _onTunerInfoRxdAction ) { AxeFXXLPlusTunerInfoDecoder->onSuccess( _onTunerInfoRxdAction ); }
		AxeFXXLPlusTunerInfoDecoder->decode( tmp2 );
		delete AxeFXXLPlusTunerInfoDecoder;
	
		AxonAxeFXXLPlusFrontPanelChangeDecoder *AxeFXXLPlusFrontPanelChangeDecoder = new AxonAxeFXXLPlusFrontPanelChangeDecoder();
		if ( _onFrontPanelChangeRxdAction ) { AxeFXXLPlusFrontPanelChangeDecoder->onSuccess( _onFrontPanelChangeRxdAction ); }
		AxeFXXLPlusFrontPanelChangeDecoder->decode( tmp2 );
		delete AxeFXXLPlusFrontPanelChangeDecoder;

		AxonAxeFXXLPlusPresetBlocksDataDecoder *AxeFXXLPlusPresetBlocksDataDecoder = new AxonAxeFXXLPlusPresetBlocksDataDecoder();
		if ( _onPresetDataBlocksDataRxdAction ) { AxeFXXLPlusPresetBlocksDataDecoder->onSuccess( _onPresetDataBlocksDataRxdAction ); }
		AxeFXXLPlusPresetBlocksDataDecoder->decode( tmp2 );
		delete AxeFXXLPlusPresetBlocksDataDecoder;

		AxonAxeFXXLPlusPresetNumberDecoder *AxeFXXLPlusPresetNumberDecoder = new AxonAxeFXXLPlusPresetNumberDecoder();
		if ( _onPresetNumberRxdAction ) { AxeFXXLPlusPresetNumberDecoder->onSuccess( _onPresetNumberRxdAction ); }
		AxeFXXLPlusPresetNumberDecoder->decode( tmp2 );
		delete AxeFXXLPlusPresetNumberDecoder;
		
		AxonAxeFXXLPlusPresetNameDecoder *AxeFXXLPlusPresetNameDecoder = new AxonAxeFXXLPlusPresetNameDecoder();
		if ( _onPresetNameRxdAction ) { AxeFXXLPlusPresetNameDecoder->onSuccess( _onPresetNameRxdAction ); }
		AxeFXXLPlusPresetNameDecoder->decode( tmp2 );
		delete AxeFXXLPlusPresetNameDecoder;
		
		AxonAxeFXXLPlusSceneNumberDecoder *AxeFXXLPlusSceneNumberDecoder = new AxonAxeFXXLPlusSceneNumberDecoder();
		if ( _onSceneNumberRxdAction ) { AxeFXXLPlusSceneNumberDecoder->onSuccess( _onSceneNumberRxdAction ); }
		AxeFXXLPlusSceneNumberDecoder->decode( tmp2 );
		delete AxeFXXLPlusSceneNumberDecoder;
	}
		
	delete tmp;
}