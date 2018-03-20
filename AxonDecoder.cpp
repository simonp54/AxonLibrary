#include "AxonDecoderTypeNumbers.h"
#include "AxonDecoder.h"

#include "AxonDebugDefines.h"

AxonDecoder::AxonDecoder( )
{
	_groupID = AXON_DECODER;
}

bool AxonDecoder::sameType( AxonDecoder *decoder )
{
#ifdef DEBUG_DECODER
	Serial.print( F(" matching ") );
	Serial.print( decoder->getGroupID(), BIN );
	Serial.print( F(" vs ") );
	Serial.print( _groupID, BIN );
	Serial.print( F(" ") );	
	(( decoder->getGroupID() & _groupID) == decoder->getGroupID()) ? Serial.println( F("MATCH") ): Serial.println( );
#endif
	
	if ((decoder->getGroupID() & _groupID) == decoder->getGroupID())
	{
		return true;
	}
	else
	{
		return false;
	}
}