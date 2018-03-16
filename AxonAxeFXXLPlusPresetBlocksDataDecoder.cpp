#include "AxonAxeFXXLPlusPresetBlocksDataDecoder.h"
#include "AxonAxeFXXLPlusBlockListContainer.h"
#include "AxonAxeFXXLPlusBlockContainer.h"
#include "AxonFASPresetBlocksDataEvent.h"
#include "AxonEventManager.h"
#include "AxonDecoderTypeNumbers.h"

#include "Arduino.h"

#include "AxonDebugDefines.h"

AxonAxeFXXLPlusPresetBlocksDataDecoder::AxonAxeFXXLPlusPresetBlocksDataDecoder()
{
	_groupID = AXON_AXEFX_XL_PLUS_PRESET_BLOCKS_DATA_DECODER_TYPE;
}

bool AxonAxeFXXLPlusPresetBlocksDataDecoder::decode( AxonSysExMidiEvent *event )
{
	// depending on our concrete type attempt to decode the buffer in the SysExEvent
	
	// return true if we decoded or false if we didn't decode
	if (AxonAxeFXXLPlusModelDecoder::decode( event ) )
	{
		if (event->getByte(5) == 0x0E)					// PRESET BLOCKS DATA MESSAGE FROM AN AXEFX XL PLUS
		{
			if (event->getSize() == 8)
			{
#ifdef DEBUG_AXON_AXEFX_XL_PLUS_PRESET_BLOCKS_DATA_DECODER_TYPE
				Serial.println( F("AxonAxeFXXLPlusPresetBlocksDataDecoder::IGNORING PRESET BLOCKS DATA REQUEST (size==8) - SUCCESS") );
#endif
				// this is a valid BUT a return of the REQUEST to retrieve the Blocks information
				// so ignore it, BUT it is "correctly" formed...
				return true;
			}
			
			uint8_t blockCount = (event->getSize() - 7) / 5;
	
#ifdef DEBUG_AXON_AXEFX_XL_PLUS_PRESET_BLOCKS_DATA_DECODER_TYPE
			Serial.print( F("AxonAxeFXXLPlusPresetBlocksDataDecoder::blockCount=") );
			Serial.println( blockCount );
#endif
			if ( blockCount > 0 )
			{
				AxonAxeFXXLPlusBlockListContainer *newList = new AxonAxeFXXLPlusBlockListContainer();
				for( uint8_t i = 0; i < blockCount; i++)
				{
					AxonAxeFXXLPlusBlockContainer *newBlock = new AxonAxeFXXLPlusBlockContainer();
					
					newBlock->setBypass( event->getByte( (i * 5) + 6) & 0x01 );
					newBlock->setXYState( event->getByte( (i * 5) + 6) & 0x02 );
					newBlock->setBlockID( ( ( event->getByte( i + 3 ) & 0x7F) >> 3) | ( (event->getByte(i + 4) & 0x7F ) << 4) );
					newBlock->setBypassCC( ( ( event->getByte( i + 1 ) & 0x7F) >> 1) | ( (event->getByte(i + 2) & 0x7F ) << 6) );
					newBlock->setXYCC( ( ( event->getByte( i + 2 ) & 0x7F) >> 2) | ( (event->getByte(i + 3) & 0x7F ) << 5) );
					
					newList->addBlock( newBlock );
				}

				AxonFASPresetBlocksDataEvent *newEvent = new AxonFASPresetBlocksDataEvent();
				newEvent->setBlockList( newList );
				AxonEventManager::instance()->addToQueue( newEvent );
				
#ifdef DEBUG_AXON_AXEFX_XL_PLUS_PRESET_BLOCKS_DATA_DECODER_TYPE
				Serial.println( F("AxonAxeFXXLPlusPresetBlocksDataDecoder::DECODED PRESET BLOCKS DATA MESSAGE - SUCCESS") );
#endif
				return true;
			}
			else
			{
#ifdef DEBUG_AXON_AXEFX_XL_PLUS_PRESET_BLOCKS_DATA_DECODER_TYPE
				Serial.println( F("AxonAxeFXXLPlusPresetBlocksDataDecoder::DECODED <EMPTY> PRESET BLOCKS DATA MESSAGE - SUCCESS") );
#endif
				return true;
			}
		}
	}
	
#ifdef DEBUG_AXON_AXEFX_XL_PLUS_PRESET_BLOCKS_DATA_DECODER_TYPE
	Serial.println( F("AxonAxeFXXLPlusPresetBlocksDataDecoder::(some other data not PRESET BLOCKS DATA)") );
#endif
	
	return false;
}