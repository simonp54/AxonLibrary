#include "AxonAFXXLPFrontPanelChangeDecoder.h"
#include "AxonDecoderTypeNumbers.h"
#include "AxonAFXXLPFrontPanelChangeEvent.h"
#include "AxonEventManager.h"
#include "Arduino.h"

#include "AxonDebugDefines.h"
#include "AxonCheckMem.h"

AxonAFXXLPFrontPanelChangeDecoder::AxonAFXXLPFrontPanelChangeDecoder()
{
	_groupID = AXON_AXEFX_XL_PLUS_FRONT_PANEL_CHANGE_DECODER;
}

bool AxonAFXXLPFrontPanelChangeDecoder::decode( AxonSysExMidiEvent *event )
{
	// depending on our concrete type attempt to decode the buffer in the SysExEvent
	
	// return true if we decoded or false if we didn't decode
	if (AxonAFXXLPChecksumDecoder::decode( event ) )
	{
		if (event->getSize() == 8)				// a front panel change message is 8 bytes in size
		{
			if ( (event->getByte(5)) == 0x21 )		// message id   aka this IS A FRONT PANEL MESSAGE
			{
				AxonAFXXLPFrontPanelChangeEvent *newEvent = new AxonAFXXLPFrontPanelChangeEvent();
				
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
				if (_onSuccess)
				{
					_onSuccess->execute( NULL, newEvent );
				}
				
				AxonEventManager::instance()->addToQueue( newEvent );
				
#ifdef DEBUG_AXEFX_XL_PLUS_FRONT_PANEL_CHANGE_DECODER
				Serial.println( F("AxonAFXXLPFrontPanelChangeDecoder::DECODED AXEFX XL+ FRONT PANEL CHANGE SYSEX MESSAGE - SUCCESS") );
#endif
				return true;
			}
		}
	}

#ifdef DEBUG_AXEFX_XL_PLUS_FRONT_PANEL_CHANGE_DECODER_VERBOSE
	Serial.println( F("AxonAFXXLPFrontPanelChangeDecoder::(some other data not FRONT PANEL CHANGE)") );
#endif

	return false;
}