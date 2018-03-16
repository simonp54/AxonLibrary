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
		if (event->getSize() == 8)						// the absolute minimum of a checksummed FAS message structure *one byte payload
		{
			if ( (event->getByte(5)) == 0x21 )
			{
				AxonFASFrontPanelChangeEvent *newEvent = new AxonFASFrontPanelChangeEvent();
				AxonEventManager::instance()->addToQueue( newEvent );
				
#ifdef DEBUG_AXON_AXEFX_XL_PLUS_FRONT_PANEL_CHANGE_DECODER_TYPE
				Serial.println( "DECODED AXEFX XL+ FRONT PANEL CHANGE SYSEX MESSAGE - SUCCESS" );
#endif
				return true;
			}
		}
#ifdef DEBUG_AXON_AXEFX_XL_PLUS_FRONT_PANEL_CHANGE_DECODER_TYPE
		Serial.print( F("SysEx Msg Size=") );
		Serial.println( event->getSize() );
		Serial.println( "UNABLE TO DECODE AXEFX XL+ FRONT PANEL CHANGE SYSEX MESSAGE");
#endif
		return false;
	}
	return false;
}