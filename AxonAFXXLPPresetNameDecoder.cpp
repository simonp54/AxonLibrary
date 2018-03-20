#include "AxonAFXXLPPresetNameDecoder.h"
#include "AxonAFXXLPPresetNameEvent.h"
#include "AxonEventManager.h"
#include "AxonGeneralStorage.h"

#include "AxonDecoderTypeNumbers.h"

#include "AxonDebugDefines.h"
#include "AxonCheckMem.h"


AxonAFXXLPPresetNameDecoder::AxonAFXXLPPresetNameDecoder()
{
	_groupID = AXON_AXEFX_XL_PLUS_PRESET_NAME_DECODER;
}

bool AxonAFXXLPPresetNameDecoder::decode( AxonSysExMidiEvent *event )
{
	// depending on our concrete type attempt to decode the buffer in the SysExEvent
	
	// return true if we decoded or false if we didn't decode
	if (AxonAFXXLPChecksumDecoder::decode( event ) )
	{
		if (event->getSize() == 40)					// a preset name message is 40 bytes in size
		{
			if ( (event->getByte(5)) == 0x0F )		// message id   aka this IS A PRESET NAME MESSAGE
			{
				AxonAFXXLPPresetNameEvent *newEvent = new AxonAFXXLPPresetNameEvent();
				
				char tmpName[AxonGeneralStorage::AXEFX_PRESET_NAME_MAXIMUM_SIZE+1];
			    uint8_t i = 6;
				while ( ( event->getByte(i) != 0x00 ) and (i < 33 + 6 ) )
				{
				  tmpName[i - 6] = event->getByte(i);
				  i++;
				}
				tmpName[i - 6] = 0x00;
				
				newEvent->setPresetName( tmpName );
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
				
				// if an ACTION handler has been setup then call the execute
				if (_onSuccess)
				{
					_onSuccess->execute( newEvent );
				}
				
				AxonEventManager::instance()->addToQueue( newEvent );

#ifdef DEBUG_AXEFX_XL_PLUS_PRESET_NUMBER_DECODER
				Serial.print( F("AxonAFXXLPPresetNameDecoder::DECODED AXEFX XL+ PRESET NAME <") );
				Serial.print( tmpName );
				Serial.println( F("> SYSEX MESSAGE - SUCCESS") );
#endif
				return true;
			}
		}
	}

#ifdef DEBUG_AXEFX_XL_PLUS_PRESET_NUMBER_DECODER_VERBOSE
	Serial.println( F("AxonAFXXLPPresetNameDecoder::(some other data not PRESET NAME)") );
#endif

	return false;
}