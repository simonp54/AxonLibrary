#include "AxonAFXXLPSceneNumberDecoder.h"
//#include "AxonHardwareSwitchEvent.h"
#include "AxonAFXXLPSceneNumberEvent.h"
#include "AxonEventManager.h"

#include "AxonDecoderTypeNumbers.h"

#include "AxonDebugDefines.h"
#include "AxonCheckMem.h"


AxonAFXXLPSceneNumberDecoder::AxonAFXXLPSceneNumberDecoder()
{
	_groupID = AXON_AXEFX_XL_PLUS_SCENE_NUMBER_DECODER;
}

bool AxonAFXXLPSceneNumberDecoder::decode( AxonSysExMidiEvent *event )
{
	// depending on our concrete type attempt to decode the buffer in the SysExEvent
	
	// return true if we decoded or false if we didn't decode
	if (AxonAFXXLPChecksumDecoder::decode( event ) )
	{
		if ( event->getSize() == 9 )				// a scene number message is 9 bytes in size
		{
			if ( event->getByte(5) == 0x29 )		// message id   aka this IS A SCENE NUMBER MESSAGE
			{
				if ( event->getByte(6) == 0x7F )	// this is a request scene number message... ignore
				{
#ifdef DEBUG_AXEFX_XL_PLUS_SCENE_NUMBER_DECODER_VERBOSE
					Serial.println( F("AxonAFXXLPSceneNumberDecoder::DECODED AXEFX XL+ SCENE NUMBER REQUEST SYSEX MESSAGE - IGNORE SUCCESS") );
#endif
					return true;
				}
				
				AxonAFXXLPSceneNumberEvent *newEvent = new AxonAFXXLPSceneNumberEvent();
				newEvent->setSceneNumber( event->getByte(6) );
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif

	
				// if an ACTION handler has been setup then call the execute
				
				if ((_onScene1Rxd)) { _onScene1Rxd->execute( NULL, newEvent ); }

//				if ((_onScene1Rxd) && (event->getByte(6) == 0)) { _onScene1Rxd->execute( NULL, newEvent ); }
//				if ((_onScene2Rxd) && (event->getByte(6) == 1)) { _onScene2Rxd->execute( NULL, newEvent ); }
//				if ((_onScene3Rxd) && (event->getByte(6) == 2)) { _onScene3Rxd->execute( NULL, newEvent ); }
//				if ((_onScene4Rxd) && (event->getByte(6) == 3)) { _onScene4Rxd->execute( NULL, newEvent ); }
//				if ((_onScene5Rxd) && (event->getByte(6) == 4)) { _onScene5Rxd->execute( NULL, newEvent ); }
//				if ((_onScene6Rxd) && (event->getByte(6) == 5)) { _onScene6Rxd->execute( NULL, newEvent ); }
//				if ((_onScene7Rxd) && (event->getByte(6) == 6)) { _onScene7Rxd->execute( NULL, newEvent ); }
//				if ((_onScene8Rxd) && (event->getByte(6) == 7)) { _onScene8Rxd->execute( NULL, newEvent ); }
				if (_onSuccess) { _onSuccess->execute( NULL, newEvent ); }
				
				AxonEventManager::instance()->addToQueue( newEvent );

#ifdef DEBUG_AXEFX_XL_PLUS_SCENE_NUMBER_DECODER
				Serial.print( F("AxonAFXXLPSceneNumberDecoder::DECODED AXEFX XL+ SCENE NUMBER <") );
				Serial.print( newEvent->getSceneNumber() );
				Serial.println( F("> SYSEX MESSAGE - SUCCESS") );
#endif
				return true;
			}
		}
	}

#ifdef DEBUG_AXEFX_XL_PLUS_SCENE_NUMBER_DECODER_VERBOSE
	Serial.println( F("AxonAFXXLPSceneNumberDecoder::(some other data not SCENE NUMBER)") );
#endif

	return false;
}