#include "AxonAFXXLPPresetNumberDecoder.h"
#include "AxonAFXXLPPresetNumberEvent.h"

#include "AxonDecoderTypeNumbers.h"

#include "AxonDebugDefines.h"
#include "AxonCheckMem.h"


AxonAFXXLPPresetNumberDecoder::AxonAFXXLPPresetNumberDecoder()
{
	_groupID = AXON_AXEFX_XL_PLUS_PRESET_NUMBER_DECODER;
}

bool AxonAFXXLPPresetNumberDecoder::decode( AxonSysExMidiEvent *event )
{
	// depending on our concrete type attempt to decode the buffer in the SysExEvent
	
	// return true if we decoded or false if we didn't decode
	if (AxonAFXXLPChecksumDecoder::decode( event ) )
	{
		if (event->getSize() == 10)				// a preset number message is 10 bytes in size
		{
			if ( (event->getByte(5)) == 0x14 )		// message id   aka this IS A PRESET NUMBER MESSAGE
			{
				AxonAFXXLPPresetNumberEvent *newEvent = new AxonAFXXLPPresetNumberEvent();
				newEvent->setPresetNumber( event->getByte(7), event->getByte(6) );
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
				
				// if an ACTION handler has been setup then call the execute
				if (_onSuccess)
				{
					_onSuccess->execute( NULL, newEvent );
				}

#ifdef DEBUG_AXEFX_XL_PLUS_PRESET_NUMBER_DECODER
				Serial.print( F("AxonAFXXLPPresetNumberDecoder::DECODED AXEFX XL+ PRESET NUMBER <") );
				Serial.print( newEvent->getPresetNumber() );
				Serial.println( F("> SYSEX MESSAGE - SUCCESS") );
#endif
				delete newEvent;
				return true;
			}
		}
	}

#ifdef DEBUG_AXEFX_XL_PLUS_PRESET_NUMBER_DECODER_VERBOSE
	Serial.println( F("AxonAFXXLPPresetNumberDecoder::(some other data not PRESET NUMBER)") );
#endif

	return false;
}