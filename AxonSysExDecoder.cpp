#include "AxonSysExDecoder.h"
#include "AxonDecoderTypeNumbers.h"
#include "Arduino.h"

#include "AxonDebugDefines.h"

AxonSysExDecoder::AxonSysExDecoder()
{
	_groupID = AXON_SYSEX_DECODER_TYPE;
}

bool AxonSysExDecoder::decode( AxonSysExMidiEvent *event )
{
	// depending on our concrete type attempt to decode the buffer in the SysExEvent
	
	// return true if we decoded or false if we didn't decode
	return false;
}