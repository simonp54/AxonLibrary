#include "AxonAFXXLPChecksumDecoder.h"
#include "AxonDecoderTypeNumbers.h"
#include "Arduino.h"

#include "AxonDebugDefines.h"

AxonAFXXLPChecksumDecoder::AxonAFXXLPChecksumDecoder()
{
	_groupID = AXON_AXEFX_XL_PLUS_CHECKSUM_DECODER;
}

bool AxonAFXXLPChecksumDecoder::decode( AxonSysExMidiEvent *event )
{
	// depending on our concrete type attempt to decode the buffer in the SysExEvent
	
	// return true if we decoded or false if we didn't decode
	if (AxonAFXXLPModelDecoder::decode( event ) )
	{
		if (event->getSize() >= 8)			// the absolute minimum of a checksummed FAS message structure *one byte payload
		{
			if ( ( event->getByte( event->getSize() - 2 ) ) == calcChecksum( event ) )
			{
//				if (_onSuccess)
//				{
//					_onSuccess->execute( event );
//				}
#ifdef DEBUG_AXEFX_XL_PLUS_CHECKSUM_DECODER
				Serial.println( F("AxonAFXXLPChecksumDecoder::CHECKSUM VALID") );
#endif
				return true;
			}
			else
			{
#ifdef DEBUG_AXEFX_XL_PLUS_CHECKSUM_DECODER
				Serial.println( F("AxonAFXXLPChecksumDecoder::CHECKSUM INVALID") );
#endif
				return true;			// even tho the checksum failed... the message was decoded "successfully"
			}
		}
	}
	return false;
}

uint8_t AxonAFXXLPChecksumDecoder::calcChecksum( AxonSysExMidiEvent *event )
{
  uint8_t checksum = 0;
  for ( uint8_t i = 0; i <= event->getSize() - 3; i++)
  {
    checksum ^= event->getByte(i);
  }
  checksum &= 0x7F;

  return checksum;
}