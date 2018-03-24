#include "AxonAFXXLPSysExAction.h"
#include "AxonSysExMidiEvent.h"
#include "AxonAFXXLPTunerInfoDecoder.h"
#include "AxonAFXXLPFrontPanelChangeDecoder.h"
#include "AxonAFXXLPPresetBlocksDataDecoder.h"
#include "AxonAFXXLPPresetNumberDecoder.h"
#include "AxonAFXXLPPresetNameDecoder.h"
#include "AxonAFXXLPSceneNumberDecoder.h"

#include "AxonDebugDefines.h"
#include "AxonCheckMem.h"


AxonAFXXLPSysExAction::AxonAFXXLPSysExAction()
{
	_AFXXLPTunerInfoDecoder = new AxonAFXXLPTunerInfoDecoder();
	_AFXXLPFrontPanelChangeDecoder = new AxonAFXXLPFrontPanelChangeDecoder();
	_AFXXLPPresetBlocksDataDecoder = new AxonAFXXLPPresetBlocksDataDecoder();
	_AFXXLPPresetNumberDecoder = new AxonAFXXLPPresetNumberDecoder();
	_AFXXLPPresetNameDecoder = new AxonAFXXLPPresetNameDecoder();
	_AFXXLPSceneNumberDecoder = new AxonAFXXLPSceneNumberDecoder();

#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
}

AxonAFXXLPSysExAction::~AxonAFXXLPSysExAction()
{
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


void AxonAFXXLPSysExAction::execute( AxonAction *action, AxonEvent *event )
{
#ifdef DEBUG_AXE_FX_XL_PLUS_SYSEX_EVENT_CLIENT
	Serial.print( F("AxonAFXXLPSysExAction::event         received:") );
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