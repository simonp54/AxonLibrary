#include "AxonAxeFXXLPlusPresetNumberDecoder.h"
#include "AxonFASPresetNumberEvent.h"
#include "AxonEventManager.h"

#include "AxonDecoderTypeNumbers.h"

#include "AxonDebugDefines.h"

AxonAxeFXXLPlusPresetNumberDecoder::AxonAxeFXXLPlusPresetNumberDecoder()
{
	_groupID = AXON_AXEFX_XL_PLUS_PRESET_NUMBER_DECODER_TYPE;
}

bool AxonAxeFXXLPlusPresetNumberDecoder::decode( AxonSysExMidiEvent *event )
{
	// depending on our concrete type attempt to decode the buffer in the SysExEvent
	
	// return true if we decoded or false if we didn't decode
	if (AxonAxeFXXLPlusChecksumDecoder::decode( event ) )
	{
		if (event->getSize() == 10)				// a preset number message is 10 bytes in size
		{
			if ( (event->getByte(5)) == 0x14 )		// message id   aka this IS A PRESET NUMBER MESSAGE
			{
				AxonFASPresetNumberEvent *newEvent = new AxonFASPresetNumberEvent();
				newEvent->setPresetNumber( event->getByte(7), event->getByte(6) );
				
				// if an ACTION handler has been setup then call the execute
				if (_onSuccess)
				{
					_onSuccess->execute( newEvent );
				}
				
				AxonEventManager::instance()->addToQueue( newEvent );

#ifdef DEBUG_AXON_AXEFX_XL_PLUS_PRESET_NUMBER_DECODER_TYPE
				Serial.print( F("AxonAxeFXXLPlusPresetNumberDecoder::DECODED AXEFX XL+ PRESET NUMBER <") );
				Serial.print( newEvent->getPresetNumber() );
				Serial.println( F("> SYSEX MESSAGE - SUCCESS") );
#endif
				return true;
			}
		}
	}

#ifdef DEBUG_AXON_AXEFX_XL_PLUS_PRESET_NUMBER_DECODER_TYPE_VERBOSE
	Serial.println( F("AxonAxeFXXLPlusPresetNumberDecoder::(some other data not PRESET NUMBER)") );
#endif

	return false;
}