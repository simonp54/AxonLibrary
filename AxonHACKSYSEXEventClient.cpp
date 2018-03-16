#include "AxonHACKSYSEXEventClient.h"
#include "AxonSysExMidiEvent.h"
#include "AxonFASManufacturerDecoder.h"
#include "AxonAxeFXXLPlusModelDecoder.h"
#include "AxonAxeFXXLPlusTunerInfoDecoder.h"
#include "AxonAxeFXXLPlusChecksumDecoder.h"
#include "AxonAxeFXXLPlusFrontPanelChangeDecoder.h"
#include "AxonAxeFXXLPlusPresetBlocksDataDecoder.h"
#include "AxonEvent.h"

#include "AxonDebugDefines.h"

void AxonHACKSYSEXEventClient::event( AxonEvent *event )
{
#ifdef DEBUG_AXON_HACK_SYSEX_EVENT_CLIENT
	Serial.print( F("AxonHACKSYSEXEventClient::event         received:") );
	Serial.println( event->getGroupID(), BIN );
#endif
	AxonSysExMidiEvent *tmp = new AxonSysExMidiEvent();

	if (event->sameType(tmp))
	{
		AxonSysExMidiEvent *tmp2 = event;
		
//		AxonFASManufacturerDecoder *FASManDec = new AxonFASManufacturerDecoder();
//		FASManDec->decode( tmp2 );
//		delete FASManDec;

//		AxonAxeFXXLPlusModelDecoder *AxeFXXLPlusModelDec = new AxonAxeFXXLPlusModelDecoder();
//		AxeFXXLPlusModelDec->decode( tmp2 );
//		delete AxeFXXLPlusModelDec;

		AxonAxeFXXLPlusTunerInfoDecoder *AxeFXXLPlusTunerInfoDecoder = new AxonAxeFXXLPlusTunerInfoDecoder();
		AxeFXXLPlusTunerInfoDecoder->decode( tmp2 );
		delete AxeFXXLPlusTunerInfoDecoder;
	
//		AxonAxeFXXLPlusChecksumDecoder *AxeFXXLPlusChecksumDecoder = new AxonAxeFXXLPlusChecksumDecoder();
//		AxeFXXLPlusChecksumDecoder->decode( tmp2 );
//		delete AxeFXXLPlusChecksumDecoder;

		AxonAxeFXXLPlusFrontPanelChangeDecoder *AxeFXXLPlusFrontPanelChangeDecoder = new AxonAxeFXXLPlusFrontPanelChangeDecoder();
		AxeFXXLPlusFrontPanelChangeDecoder->decode( tmp2 );
		delete AxeFXXLPlusFrontPanelChangeDecoder;

		AxonAxeFXXLPlusPresetBlocksDataDecoder *AxeFXXLPlusPresetBlocksDataDecoder = new AxonAxeFXXLPlusPresetBlocksDataDecoder();
		AxeFXXLPlusPresetBlocksDataDecoder->decode( tmp2 );
		delete AxeFXXLPlusPresetBlocksDataDecoder;

	}
		
	delete tmp;
	

//	this could be how multiple events are handled in this single client
//  but possibly this will confuse the clarity of a single event being handled
//  consider multiple clients ......
//	AxonFASFrontPanelChangeEvent *tmp = new AxonFASFrontPanelChangeEvent();
//	if (event->sameType(tmp))
//	{
//		// run on action for a frontpanelchange
//	}
//	delete tmp;
}