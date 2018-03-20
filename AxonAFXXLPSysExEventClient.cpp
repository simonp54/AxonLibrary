#include "AxonAFXXLPSysExEventClient.h"
#include "AxonSysExMidiEvent.h"
#include "AxonAFXXLPTunerInfoDecoder.h"
#include "AxonAFXXLPFrontPanelChangeDecoder.h"
#include "AxonAFXXLPPresetBlocksDataDecoder.h"
#include "AxonAFXXLPPresetNumberDecoder.h"
#include "AxonAFXXLPPresetNameDecoder.h"
#include "AxonAFXXLPSceneNumberDecoder.h"
#include "AxonEvent.h"

#include "AxonDebugDefines.h"
#include "AxonCheckMem.h"


AxonAFXXLPSysExEventClient::AxonAFXXLPSysExEventClient()
{
	_AFXXLPTunerInfoDecoder = new AxonAFXXLPTunerInfoDecoder();
	_AFXXLPFrontPanelChangeDecoder = new AxonAFXXLPFrontPanelChangeDecoder();
	_AFXXLPPresetBlocksDataDecoder = new AxonAFXXLPPresetBlocksDataDecoder();
	_AFXXLPPresetNumberDecoder = new AxonAFXXLPPresetNumberDecoder();
	_AFXXLPPresetNameDecoder = new AxonAFXXLPPresetNameDecoder();
	_AFXXLPSceneNumberDecoder = new AxonAFXXLPSceneNumberDecoder();

	_sysExMidiEvent = new AxonSysExMidiEvent();
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
	
	AxonEventManager::instance()->clientRegister( this, _sysExMidiEvent );
}

AxonAFXXLPSysExEventClient::~AxonAFXXLPSysExEventClient()
{
	AxonEventManager::instance()->clientDeregister( this );
	delete _sysExMidiEvent;

	delete _AFXXLPSceneNumberDecoder;
	delete _AFXXLPPresetNameDecoder;
	delete _AFXXLPPresetNumberDecoder;
	delete _AFXXLPPresetBlocksDataDecoder;
	delete _AFXXLPFrontPanelChangeDecoder;
	delete _AFXXLPTunerInfoDecoder;
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
}


void AxonAFXXLPSysExEventClient::event( AxonEvent *event )
{
#ifdef DEBUG_AXE_FX_SYSEX_EVENT_CLIENT
	Serial.print( F("AxonAFXXLPSysExEventClient::event         received:") );
	Serial.println( event->getGroupID(), BIN );
#endif
	AxonSysExMidiEvent *tmp = new AxonSysExMidiEvent();
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif

	if (event->sameType(tmp))
	{
		AxonSysExMidiEvent *tmp2 = event;
	
		bool continueDecodeChecks = _AFXXLPTunerInfoDecoder->decode( tmp2 );
		if (!continueDecodeChecks) { continueDecodeChecks = _AFXXLPFrontPanelChangeDecoder->decode( tmp2 ); }
		if (!continueDecodeChecks) { continueDecodeChecks = _AFXXLPSceneNumberDecoder->decode( tmp2 ); }
		if (!continueDecodeChecks) { continueDecodeChecks = _AFXXLPPresetNumberDecoder->decode( tmp2 ); }
		if (!continueDecodeChecks) { continueDecodeChecks = _AFXXLPPresetNameDecoder->decode( tmp2 ); }
		if (!continueDecodeChecks) { continueDecodeChecks = _AFXXLPPresetBlocksDataDecoder->decode( tmp2 ); }
	}
		
	delete tmp;
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
}