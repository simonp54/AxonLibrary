#include "AxonAFXXLPPresetBlocksDataDecoder.h"
#include "AxonAFXXLPBlockListContainer.h"
#include "AxonAFXXLPBlockContainer.h"
#include "AxonAFXXLPPresetBlocksDataEvent.h"
#include "AxonEventManager.h"
#include "AxonDecoderTypeNumbers.h"

#include "Arduino.h"

#include "AxonDebugDefines.h"
#include "AxonCheckMem.h"

AxonAFXXLPPresetBlocksDataDecoder::AxonAFXXLPPresetBlocksDataDecoder()
{
	_groupID = AXON_AXEFX_XL_PLUS_PRESET_BLOCKS_DATA_DECODER;
}

bool AxonAFXXLPPresetBlocksDataDecoder::decode( AxonSysExMidiEvent *event )
{
	// depending on our concrete type attempt to decode the buffer in the SysExEvent
	
	// return true if we decoded or false if we didn't decode
	if (AxonAFXXLPModelDecoder::decode( event ) )
	{
		if (event->getByte(5) == 0x0E)					// PRESET BLOCKS DATA MESSAGE FROM AN AXEFX XL PLUS
		{
			if (event->getSize() == 8)
			{
#ifdef DEBUG_AXEFX_XL_PLUS_PRESET_BLOCKS_DATA_DECODER_VERBOSE
				Serial.println( F("AxonAFXXLPPresetBlocksDataDecoder::IGNORING PRESET BLOCKS DATA REQUEST (size==8) - SUCCESS") );
#endif
				// this is a valid BUT a return of the REQUEST to retrieve the Blocks information
				// so ignore it, BUT it is "correctly" formed...
				return true;
			}
			
			uint8_t blockCount = (event->getSize() - 7) / 5;
	
#ifdef DEBUG_AXEFX_XL_PLUS_PRESET_BLOCKS_DATA_DECODER_VERBOSE
			Serial.print( F("AxonAFXXLPPresetBlocksDataDecoder::blockCount=") );
			Serial.println( blockCount );
#endif
			if ( blockCount > 0 )
			{
/*
				AxonAFXXLPBlockListContainer *newList = new AxonAFXXLPBlockListContainer();
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
				for( uint8_t i = 0; i < blockCount; i++)
				{
					AxonAFXXLPBlockContainer *newBlock = new AxonAFXXLPBlockContainer();
					
					newBlock->setBypass( event->getByte( (i * 5) + 6) & 0x01 );
					newBlock->setXYState( event->getByte( (i * 5) + 6) & 0x02 );
					newBlock->setBlockID( ( ( event->getByte( i + 3 ) & 0x7F) >> 3) | ( (event->getByte(i + 4) & 0x7F ) << 4) );
					newBlock->setBypassCC( ( ( event->getByte( i + 1 ) & 0x7F) >> 1) | ( (event->getByte(i + 2) & 0x7F ) << 6) );
					newBlock->setXYCC( ( ( event->getByte( i + 2 ) & 0x7F) >> 2) | ( (event->getByte(i + 3) & 0x7F ) << 5) );
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
					
					newList->addBlock( newBlock );
				}

				AxonAFXXLPPresetBlocksDataEvent *newEvent = new AxonAFXXLPPresetBlocksDataEvent();
				newEvent->setBlockList( newList );
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
				
//				if (_onSuccess)
//				{
//					_onSuccess->execute( newEvent );
//				}
				
				AxonEventManager::instance()->addToQueue( newEvent );
	*/			
#ifdef DEBUG_AXEFX_XL_PLUS_PRESET_BLOCKS_DATA_DECODER
				Serial.println( F("AxonAFXXLPPresetBlocksDataDecoder::DECODED PRESET BLOCKS DATA MESSAGE - SUCCESS") );
#endif
				return true;
			}
			else
			{
#ifdef DEBUG_AXEFX_XL_PLUS_PRESET_BLOCKS_DATA_DECODER
				Serial.println( F("AxonAFXXLPPresetBlocksDataDecoder::DECODED <EMPTY> PRESET BLOCKS DATA MESSAGE - SUCCESS") );
#endif
				return true;
			}
		}
	}
	
#ifdef DEBUG_AXEFX_XL_PLUS_PRESET_BLOCKS_DATA_DECODER_VERBOSE
	Serial.println( F("AxonAFXXLPPresetBlocksDataDecoder::(some other data not PRESET BLOCKS DATA)") );
#endif
	
	return false;
}