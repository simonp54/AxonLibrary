#include "AxonAxeFXXLPlusPresetNameDecoder.h"
#include "AxonFASPresetNameEvent.h"
#include "AxonEventManager.h"
#include "AxonGeneralStorage.h"

#include "AxonDecoderTypeNumbers.h"

#include "AxonDebugDefines.h"

AxonAxeFXXLPlusPresetNameDecoder::AxonAxeFXXLPlusPresetNameDecoder()
{
	_groupID = AXON_AXEFX_XL_PLUS_PRESET_NAME_DECODER_TYPE;
}

bool AxonAxeFXXLPlusPresetNameDecoder::decode( AxonSysExMidiEvent *event )
{
	// depending on our concrete type attempt to decode the buffer in the SysExEvent
	
	// return true if we decoded or false if we didn't decode
	if (AxonAxeFXXLPlusChecksumDecoder::decode( event ) )
	{
		if (event->getSize() == 40)					// a preset name message is 40 bytes in size
		{
			if ( (event->getByte(5)) == 0x0F )		// message id   aka this IS A PRESET NAME MESSAGE
			{
				AxonFASPresetNameEvent *newEvent = new AxonFASPresetNameEvent();
				
				char tmpName[AxonGeneralStorage::AXEFX_PRESET_NAME_MAXIMUM_SIZE+1];
			    uint8_t i = 6;
				while ( ( event->getByte(i) != 0x00 ) and (i < 33 + 6 ) )
				{
				  tmpName[i - 6] = event->getByte(i);
				  i++;
				}
				tmpName[i - 6] = 0x00;
				
				newEvent->setPresetName( tmpName );
				
				// if an ACTION handler has been setup then call the execute
				if (_onSuccess)
				{
					_onSuccess->execute( newEvent );
				}
				
				AxonEventManager::instance()->addToQueue( newEvent );

#ifdef DEBUG_AXON_AXEFX_XL_PLUS_PRESET_NUMBER_DECODER_TYPE
				Serial.print( F("AxonAxeFXXLPlusPresetNameDecoder::DECODED AXEFX XL+ PRESET NAME <") );
				Serial.print( tmpName );
				Serial.println( F("> SYSEX MESSAGE - SUCCESS") );
#endif
				return true;
			}
		}
	}

#ifdef DEBUG_AXON_AXEFX_XL_PLUS_PRESET_NUMBER_DECODER_TYPE_VERBOSE
	Serial.println( F("AxonAxeFXXLPlusPresetNameDecoder::(some other data not PRESET NAME)") );
#endif

	return false;
}