#include "AxonAxeFXXLPlusTunerInfoDecoder.h"
#include "AxonDecoderTypeNumbers.h"
#include "AxonTouchScreen.h"
#include "Arduino.h"

#include "AxonDebugDefines.h"

AxonAxeFXXLPlusTunerInfoDecoder::AxonAxeFXXLPlusTunerInfoDecoder()
{
	_groupID = AXON_AXEFX_XL_PLUS_TUNER_INFO_DECODER_TYPE;
}

bool AxonAxeFXXLPlusTunerInfoDecoder::decode( AxonSysExMidiEvent *event )
{
	// depending on our concrete type attempt to decode the buffer in the SysExEvent
	
	// return true if we decoded or false if we didn't decode
	if (AxonAxeFXXLPlusModelDecoder::decode( event ) )
	{
		if ( (event->getSize() == 10) && (event->getByte(5) == 0x0D) )
		{
//			AxonAxeFX_XL_Plus_TunerInfoEvent newEvent = new AxonAxeFX_XL_Plus_TunerInfoEvent();
			
//			newEvent->setNote(event->getByte(5));
//			newEvent->setString(event->getByte(6));
//			newEvent->setTunerData(event->getByte(7));

//			AxonEventManager::instance()->addToQueue( newEvent );

			AxonTouchScreen::instance()->setTunerNote( event->getByte(6) );
			AxonTouchScreen::instance()->setTunerString( event->getByte(7) );
			AxonTouchScreen::instance()->setTunerData( event->getByte(8) );
			
#ifdef DEBUG_AXON_AXEFX_XL_PLUS_TUNER_INFO_DECODER_TYPE
			Serial.println( F("AxonAxeFXXLPlusTunerInfoDecoder::TUNER INFO SYSEX MESSAGE - SUCCESS") );
#endif
			
			return true;
		}
	}

#ifdef DEBUG_AXON_AXEFX_XL_PLUS_TUNER_INFO_DECODER_TYPE
	Serial.println( F("AxonAxeFXXLPlusTunerInfoDecoder::(some other data not TUNER INFO)") );
#endif

	return false;
}