#include "AxonAxeFXXLPlusBlockListContainer.h"

#include "AxonDebugDefines.h"

AxonAxeFXXLPlusBlockListContainer::AxonAxeFXXLPlusBlockListContainer()
{
	_blockCount = 0;
}

AxonAxeFXXLPlusBlockListContainer::~AxonAxeFXXLPlusBlockListContainer()
{
	for( uint8_t i = 0; i < _blockCount; i++ )
	{
		delete(_blockList[i]);
	}
	_blockCount = 0;
}

void AxonAxeFXXLPlusBlockListContainer::addBlock( AxonAxeFXXLPlusBlockContainer *block )
{
	if (_blockCount < _MAX_BLOCKS)
	{
		_blockList[_blockCount] = block;
		_blockCount++;
#ifdef DEBUG_AXON_AXEFX_XL_PLUS_BLOCK_LIST_CONTAINER
		Serial.print( F("AxonAxeFXXLPlusBlockListContainer::added block (") );
		Serial.print( _blockCount );
		Serial.println( F(") total blocks") );
#endif
	}
}

void AxonAxeFXXLPlusBlockListContainer::removeBlock(AxonAxeFXXLPlusBlockContainer *block)				// find the pointer "match" shuffle the list up and lower the count "if found"
{
	bool found = false;
#ifdef DEBUG_AXON_AXEFX_XL_PLUS_BLOCK_LIST_CONTAINER
	Serial.println( F("AxonAxeFXXLPlusBlockListContainer::remove block ") );
#endif
	for( uint8_t i = 0; i < _blockCount; i++ )
	{
		if (found)
		{
			_blockList[i] = _blockList[i+1];
		}
		else if (_blockList[i] == block)
		{
#ifdef DEBUG_AXON_AXEFX_XL_PLUS_BLOCK_LIST_CONTAINER
	Serial.print( F("AxonAxeFXXLPlusBlockListContainer::  found") );
#endif
			found = true;
			_blockList[i] = _blockList[i+1];
			_blockCount--;
#ifdef DEBUG_AXON_AXEFX_XL_PLUS_BLOCK_LIST_CONTAINER
	Serial.print( F("AxonAxeFXXLPlusBlockListContainer::  and reduce block count (") );
	Serial.print( _blockCount );
	Serial.println( F(")") );
#endif
		}
	}
#ifdef DEBUG_AXON_AXEFX_XL_PLUS_BLOCK_LIST_CONTAINER
	Serial.print( F("AxonAxeFXXLPlusBlockListContainer::Blocks (") );
	Serial.print( _blockCount );
	Serial.println( F(")") );
#endif
}

AxonAxeFXXLPlusBlockContainer *AxonAxeFXXLPlusBlockListContainer::getBlock( uint8_t blockNum )
{
	if (blockNum < _blockCount)
	{
		return _blockList[blockNum];
	}
	else
	{
		return NULL;
	}
}
