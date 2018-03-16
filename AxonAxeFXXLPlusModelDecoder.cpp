#include "AxonAxeFXXLPlusModelDecoder.h"
#include "AxonDecoderTypeNumbers.h"
#include "Arduino.h"

#include "AxonDebugDefines.h"

AxonAxeFXXLPlusModelDecoder::AxonAxeFXXLPlusModelDecoder()
{
	_groupID = AXON_AXEFX_XL_PLUS_MODEL_DECODER_TYPE;
}

bool AxonAxeFXXLPlusModelDecoder::decode( AxonSysExMidiEvent *event )
{
	// depending on our concrete type attempt to decode the buffer in the SysExEvent
	
	// return true if we decoded or false if we didn't decode
	if (AxonFASManufacturerDecoder::decode( event ))
	{
		if (event->getSize() >= 6)
		{
			if ( (event->getByte(4) == 0x07) )
			{
//				AxonFASManufacturerEvent newEvent = new AxonFASManufacturerEvent();
//				AxonEventManager::instance()->addToQueue( newEvent );
#ifdef DEBUG_AXON_AXEFX_XL_PLUS_MODEL_DECODER_TYPE
				Serial.println( "DECODED AXEFX XL+ MODEL SYSEX MESSAGE - SUCCESS" );
#endif
				
				return true;
			}
		}
	}
		
#ifdef DEBUG_AXON_AXEFX_XL_PLUS_MODEL_DECODER_TYPE
	Serial.println( "UNABLE TO DECODE AXEFX XL+ MODEL SYSEX MESSAGE");
#endif
	return false;
}