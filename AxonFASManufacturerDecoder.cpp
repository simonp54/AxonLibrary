#include "AxonFASManufacturerDecoder.h"
#include "AxonDecoderTypeNumbers.h"
#include "Arduino.h"

#include "AxonDebugDefines.h"

AxonFASManufacturerDecoder::AxonFASManufacturerDecoder()
{
	_groupID = AXON_FAS_MANUFACTURER_DECODER_TYPE;
}

bool AxonFASManufacturerDecoder::decode( AxonSysExMidiEvent *event )
{
	// depending on our concrete type attempt to decode the buffer in the SysExEvent
	
	// return true if we decoded or false if we didn't decode
	if (event->getSize() >= 5)
	{
		if ((event->getByte(1) == 0x00)  && (event->getByte(2) == 0x01) && (event->getByte(3) == 0x74) )
		{
//			AxonFASManufacturerEvent newEvent = new AxonFASManufacturerEvent();
//			AxonEventManager::instance()->addToQueue( newEvent );
#ifdef DEBUG_AXON_FAS_MANUFACTURER_DECODER_TYPE
			Serial.println( "DECODED FAS SYSEX MESSAGE - SUCCESS" );
#endif
			return true;
		}
	}
	
#ifdef DEBUG_AXON_FAS_MANUFACTURER_DECODER_TYPE
	Serial.println( "UNABLE TO DECODE FAS SYSEX MESSAGE");
#endif
	return false;
}