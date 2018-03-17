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
//				if (_onSuccess)
//				{
//					_onSuccess->execute( event );
//				}

#ifdef DEBUG_AXON_AXEFX_XL_PLUS_MODEL_DECODER_TYPE
				Serial.println( F("AxonAxeFXXLPlusModelDecoder::AXEFX XL+ MODEL") );
#endif
				return true;
			}
			else
			{
#ifdef DEBUG_AXON_AXEFX_XL_PLUS_MODEL_DECODER_TYPE_VERBOSE
				Serial.println( F("AxonAxeFXXLPlusModelDecoder::UNHANDLED MODEL (0x") );
				Serial.print  ( event->getByte(4), HEX );
				Serial.println( F(") RECEIVED SYSEX MESSAGE - NO ACTION") );
#endif
			}
		}
	}
	return false;
}