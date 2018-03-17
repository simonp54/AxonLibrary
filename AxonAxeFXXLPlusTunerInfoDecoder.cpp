#include "AxonAxeFXXLPlusTunerInfoDecoder.h"
#include "AxonDecoderTypeNumbers.h"
#include "AxonFASTunerInfoEvent.h"
#include "AxonEventManager.h"
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
			AxonFASTunerInfoEvent *newEvent = new AxonFASTunerInfoEvent();
			
			newEvent->setNote(event->getByte(6));
			newEvent->setString(event->getByte(7));
			newEvent->setData(event->getByte(8));

			if (_onSuccess)
			{
				_onSuccess->execute( newEvent );
			}

			AxonEventManager::instance()->addToQueue( newEvent );
			
#ifdef DEBUG_AXON_AXEFX_XL_PLUS_TUNER_INFO_DECODER_TYPE
			Serial.println( F("AxonAxeFXXLPlusTunerInfoDecoder::TUNER INFO SYSEX MESSAGE - SUCCESS") );
#endif
			
			return true;
		}
	}

#ifdef DEBUG_AXON_AXEFX_XL_PLUS_TUNER_INFO_DECODER_TYPE_VERBOSE
	Serial.println( F("AxonAxeFXXLPlusTunerInfoDecoder::(some other data not TUNER INFO)") );
#endif

	return false;
}