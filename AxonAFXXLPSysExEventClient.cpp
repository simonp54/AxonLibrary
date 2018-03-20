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
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
	_AFXXLPFrontPanelChangeDecoder = new AxonAFXXLPFrontPanelChangeDecoder();
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
	_AFXXLPPresetBlocksDataDecoder = new AxonAFXXLPPresetBlocksDataDecoder();
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
	_AFXXLPPresetNumberDecoder = new AxonAFXXLPPresetNumberDecoder();
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
	_AFXXLPPresetNameDecoder = new AxonAFXXLPPresetNameDecoder();
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
	_AFXXLPSceneNumberDecoder = new AxonAFXXLPSceneNumberDecoder();
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif

	_sysExMidiEvent = new AxonSysExMidiEvent();
	
	AxonEventManager::instance()->clientRegister( this, _sysExMidiEvent );
}

AxonAFXXLPSysExEventClient::~AxonAFXXLPSysExEventClient()
{
	AxonEventManager::instance()->clientDeregister( this );
	delete _sysExMidiEvent;

	delete _AFXXLPTunerInfoDecoder;
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
	delete _AFXXLPFrontPanelChangeDecoder;
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif

	delete _AFXXLPPresetBlocksDataDecoder;
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif

	delete _AFXXLPPresetNumberDecoder;
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif

	delete _AFXXLPPresetNameDecoder;
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif

	delete _AFXXLPSceneNumberDecoder;
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
		
		bool shouldIStop = false;

		shouldIStop = _AFXXLPTunerInfoDecoder->decode( tmp2 );
		if (!shouldIStop) { shouldIStop = _AFXXLPFrontPanelChangeDecoder->decode( tmp2 ); }
		if (!shouldIStop) { shouldIStop = _AFXXLPSceneNumberDecoder->decode( tmp2 ); }
		if (!shouldIStop) { shouldIStop = _AFXXLPPresetNumberDecoder->decode( tmp2 ); }
		if (!shouldIStop) { shouldIStop = _AFXXLPPresetNameDecoder->decode( tmp2 ); }
		if (!shouldIStop) { shouldIStop = _AFXXLPPresetBlocksDataDecoder->decode( tmp2 ); }
	}
		
	delete tmp;
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
}