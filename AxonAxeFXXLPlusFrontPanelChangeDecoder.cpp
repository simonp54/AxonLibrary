#include "AxonAxeFXXLPlusFrontPanelChangeDecoder.h"
#include "AxonDecoderTypeNumbers.h"
#include "AxonFASFrontPanelChangeEvent.h"
#include "AxonEventManager.h"
#include "Arduino.h"

#include "AxonDebugDefines.h"

AxonAxeFXXLPlusFrontPanelChangeDecoder::AxonAxeFXXLPlusFrontPanelChangeDecoder()
{
	_groupID = AXON_AXEFX_XL_PLUS_FRONT_PANEL_CHANGE_DECODER_TYPE;
}

bool AxonAxeFXXLPlusFrontPanelChangeDecoder::decode( AxonSysExMidiEvent *event )
{
	// depending on our concrete type attempt to decode the buffer in the SysExEvent
	
	// return true if we decoded or false if we didn't decode
	if (AxonAxeFXXLPlusChecksumDecoder::decode( event ) )
	{
		if (event->getSize() == 8)				// a front panel change message is 8 bytes in size
		{
			if ( (event->getByte(5)) == 0x21 )		// message id   aka this IS A FRONT PANEL MESSAGE
			{
				AxonFASFrontPanelChangeEvent *newEvent = new AxonFASFrontPanelChangeEvent();
				AxonEventManager::instance()->addToQueue( newEvent );
				
#ifdef DEBUG_AXON_AXEFX_XL_PLUS_FRONT_PANEL_CHANGE_DECODER_TYPE
				Serial.println( F("AxonAxeFXXLPlusFrontPanelChangeDecoder::DECODED AXEFX XL+ FRONT PANEL CHANGE SYSEX MESSAGE - SUCCESS") );
#endif
				return true;
			}
		}
	}

#ifdef DEBUG_AXON_AXEFX_XL_PLUS_FRONT_PANEL_CHANGE_DECODER_TYPE
	Serial.println( F("AxonAxeFXXLPlusFrontPanelChangeDecoder::(some other data not FRONT PANEL CHANGE)") );
#endif

	return false;
}