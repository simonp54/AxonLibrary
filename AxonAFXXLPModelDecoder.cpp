#include "AxonAFXXLPModelDecoder.h"
#include "AxonDecoderTypeNumbers.h"
#include "Arduino.h"

#include "AxonDebugDefines.h"

AxonAFXXLPModelDecoder::AxonAFXXLPModelDecoder()
{
	_groupID = AXON_AXEFX_XL_PLUS_MODEL_DECODER;
}

bool AxonAFXXLPModelDecoder::decode( AxonSysExMidiEvent *event )
{
	// depending on our concrete type attempt to decode the buffer in the SysExEvent
	
	// return true if we decoded or false if we didn't decode
	if (AxonFASManufacturerDecoder::decode( event ))
	{
		if (event->getSize() >= 6)
		{
			if ( (event->getByte(4) == 0x07) )
			{
#ifdef DEBUG_AXEFX_XL_PLUS_MODEL_DECODER
				Serial.println( F("AxonAFXXLPModelDecoder::AXEFX XL+ MODEL") );
#endif
				return true;
			}
			else
			{
#ifdef DEBUG_AXEFX_XL_PLUS_MODEL_DECODER_VERBOSE
				Serial.println( F("AxonAFXXLPModelDecoder::UNHANDLED MODEL (0x") );
				Serial.print  ( event->getByte(4), HEX );
				Serial.println( F(") RECEIVED SYSEX MESSAGE - NO ACTION") );
#endif
			}
		}
	}
	return false;
}