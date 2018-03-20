#include "AxonAFXXLPTunerInfoDecoder.h"
#include "AxonDecoderTypeNumbers.h"
#include "AxonAFXXLPTunerInfoEvent.h"
#include "AxonEventManager.h"
#include "Arduino.h"

#include "AxonDebugDefines.h"
#include "AxonCheckMem.h"


AxonAFXXLPTunerInfoDecoder::AxonAFXXLPTunerInfoDecoder()
{
	_groupID = AXON_AXEFX_XL_PLUS_TUNER_INFO_DECODER;
}

bool AxonAFXXLPTunerInfoDecoder::decode( AxonSysExMidiEvent *event )
{
	// depending on our concrete type attempt to decode the buffer in the SysExEvent
	
	// return true if we decoded or false if we didn't decode
	if (AxonAFXXLPModelDecoder::decode( event ) )
	{
		if ( (event->getSize() == 10) && (event->getByte(5) == 0x0D) )
		{
			AxonAFXXLPTunerInfoEvent *newEvent = new AxonAFXXLPTunerInfoEvent();
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
			
			newEvent->setNote(event->getByte(6));
			newEvent->setString(event->getByte(7));
			newEvent->setData(event->getByte(8));

			if (_onSuccess)
			{
				_onSuccess->execute( newEvent );
			}

			AxonEventManager::instance()->addToQueue( newEvent );
			
#ifdef DEBUG_AXEFX_XL_PLUS_TUNER_INFO_DECODER
			Serial.println( F("AxonAFXXLPTunerInfoDecoder::TUNER INFO SYSEX MESSAGE - SUCCESS") );
#endif
			
			return true;
		}
	}

#ifdef DEBUG_AXEFX_XL_PLUS_TUNER_INFO_DECODER_VERBOSE
	Serial.println( F("AxonAFXXLPTunerInfoDecoder::(some other data not TUNER INFO)") );
#endif

	return false;
}