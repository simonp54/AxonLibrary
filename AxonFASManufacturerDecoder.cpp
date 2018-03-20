#include "AxonFASManufacturerDecoder.h"
#include "AxonDecoderTypeNumbers.h"
#include "Arduino.h"

#include "AxonDebugDefines.h"

AxonFASManufacturerDecoder::AxonFASManufacturerDecoder()
{
	_groupID = AXON_FAS_MANUFACTURER_DECODER;
}

bool AxonFASManufacturerDecoder::decode( AxonSysExMidiEvent *event )
{
	// depending on our concrete type attempt to decode the buffer in the SysExEvent
	
	// return true if we decoded or false if we didn't decode
	
	if (event->getSize() >= 5)
	{
		if ((event->getByte(1) == 0x00)  && (event->getByte(2) == 0x01) && (event->getByte(3) == 0x74) )
		{
#ifdef DEBUG_FAS_MANUFACTURER_DECODER
			Serial.println( F("AxonFASManufacturerDecoder::FRACTAL AUDIO SYSTEMS SYSEX MESSAGE - SUCCESS") );
#endif
			return true;
		}
		else
		{
#ifdef DEBUG_FAS_MANUFACTURER_DECODER_VERBOSE
			Serial.println( F("AxonFASManufacturerDecoder::(some other data not FRACTAL AUDIO SYSTEMS)") );
#endif
		}
	}
	return false;
}