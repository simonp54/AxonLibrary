#include "AxonAxeFXXLPlusSceneNumberDecoder.h"
#include "AxonHardwareSwitchEvent.h"
#include "AxonEventManager.h"

#include "AxonDecoderTypeNumbers.h"

#include "AxonDebugDefines.h"

AxonAxeFXXLPlusSceneNumberDecoder::AxonAxeFXXLPlusSceneNumberDecoder()
{
	_groupID = AXON_AXEFX_XL_PLUS_SCENE_NUMBER_DECODER_TYPE;
}

bool AxonAxeFXXLPlusSceneNumberDecoder::decode( AxonSysExMidiEvent *event )
{
	// depending on our concrete type attempt to decode the buffer in the SysExEvent
	
	// return true if we decoded or false if we didn't decode
	if (AxonAxeFXXLPlusChecksumDecoder::decode( event ) )
	{
		if ( event->getSize() == 9 )				// a scene number message is 9 bytes in size
		{
			if ( event->getByte(5) == 0x29 )		// message id   aka this IS A SCENE NUMBER MESSAGE
			{
				if ( event->getByte(6) == 0x7F )	// this is a request scene number message... ignore
				{
#ifdef DEBUG_AXON_AXEFX_XL_PLUS_SCENE_NUMBER_DECODER_TYPE_VERBOSE
					Serial.println( F("AxonAxeFXXLPlusSceneNumberDecoder::DECODED AXEFX XL+ SCENE NUMBER REQUEST SYSEX MESSAGE - IGNORE SUCCESS") );
#endif
					return true;
				}
				
//				AxonFASSceneNumberEvent *newEvent = new AxonFASSceneNumberEvent();
//				newEvent->setSceneNumber( event->getByte(6) );
				AxonHardwareSwitchEvent *newEvent = new AxonHardwareSwitchEvent( event->getByte(6) + 16 );
				newEvent->setSwitchState( true );
	
				// if an ACTION handler has been setup then call the execute
				if (_onSuccess)
				{
					_onSuccess->execute( newEvent );
				}
				
				AxonEventManager::instance()->addToQueue( newEvent );

#ifdef DEBUG_AXON_AXEFX_XL_PLUS_SCENE_NUMBER_DECODER_TYPE
				Serial.print( F("AxonAxeFXXLPlusSceneNumberDecoder::DECODED AXEFX XL+ SCENE NUMBER <") );
				Serial.print( newEvent->getSwitchNumber() - 16 );
				Serial.println( F("> SYSEX MESSAGE - SUCCESS") );
#endif
				return true;
			}
		}
	}

#ifdef DEBUG_AXON_AXEFX_XL_PLUS_SCENE_NUMBER_DECODER_TYPE_VERBOSE
	Serial.println( F("AxonAxeFXXLPlusSceneNumberDecoder::(some other data not SCENE NUMBER)") );
#endif

	return false;
}