#include "AxonAxeFXXLPlusChecksumDecoder.h"
#include "AxonDecoderTypeNumbers.h"
#include "Arduino.h"

#include "AxonDebugDefines.h"

AxonAxeFXXLPlusChecksumDecoder::AxonAxeFXXLPlusChecksumDecoder()
{
	_groupID = AXON_AXEFX_XL_PLUS_CHECKSUM_DECODER_TYPE;
}

bool AxonAxeFXXLPlusChecksumDecoder::decode( AxonSysExMidiEvent *event )
{
	// depending on our concrete type attempt to decode the buffer in the SysExEvent
	
	// return true if we decoded or false if we didn't decode
	if (AxonAxeFXXLPlusModelDecoder::decode( event ) )
	{
		if (event->getSize() >= 8)						// the absolute minimum of a checksummed FAS message structure *one byte payload
		{
			if ( (event->getByte( event->getSize() - 2)) == calcChecksum( event ) )
			{
#ifdef DEBUG_AXON_AXEFX_XL_PLUS_CHECKSUM_DECODER_TYPE
				Serial.println( "DECODED AXEFX XL+ CHECKSUM SYSEX MESSAGE - SUCCESS" );
#endif
				return true;
			}
			else
			{
#ifdef DEBUG_AXON_AXEFX_XL_PLUS_CHECKSUM_DECODER_TYPE
				Serial.println( "DECODED AXEFX XL+ CHECKSUM SYSEX MESSAGE - INVALID CHECKSUM");
#endif
				return false;
			}
		}
#ifdef DEBUG_AXON_AXEFX_XL_PLUS_CHECKSUM_DECODER_TYPE
		Serial.println( "UNABLE TO DECODE AXEFX XL+ CHECKSUM SYSEX MESSAGE");
#endif
		return false;
	}
	return false;
}


/****************************************************
    
 ****************************************************/
uint8_t AxonAxeFXXLPlusChecksumDecoder::calcChecksum( AxonSysExMidiEvent *event )
{
  uint8_t checksum = 0;
  for ( uint8_t i = 0; i <= event->getSize() - 3; i++)
  {
    checksum ^= event->getByte(i);
  }
  checksum &= 0x7F;

  return checksum;
}