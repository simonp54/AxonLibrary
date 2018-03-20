#include "AxonAFXXLPBlockListContainer.h"

#include "AxonDebugDefines.h"

AxonAFXXLPBlockListContainer::AxonAFXXLPBlockListContainer()
{
	_blockCount = 0;
}

AxonAFXXLPBlockListContainer::~AxonAFXXLPBlockListContainer()
{
	for( uint8_t i = 0; i < _blockCount; i++ )
	{
		delete(_blockList[i]);
	}
	_blockCount = 0;
}

void AxonAFXXLPBlockListContainer::addBlock( AxonAFXXLPBlockContainer *block )
{
	if (_blockCount < _MAX_BLOCKS)
	{
		_blockList[_blockCount] = block;
		_blockCount++;
#ifdef DEBUG_AXEFX_XL_PLUS_BLOCK_LIST_CONTAINER
		Serial.print( F("AxonAFXXLPBlockListContainer::added block (") );
		Serial.print( _blockCount );
		Serial.println( F(") total blocks") );
#endif
	}
}

void AxonAFXXLPBlockListContainer::removeBlock(AxonAFXXLPBlockContainer *block)				// find the pointer "match" shuffle the list up and lower the count "if found"
{
	bool found = false;
#ifdef DEBUG_AXEFX_XL_PLUS_BLOCK_LIST_CONTAINER
	Serial.println( F("AxonAFXXLPBlockListContainer::remove block ") );
#endif
	for( uint8_t i = 0; i < _blockCount; i++ )
	{
		if (found)
		{
			_blockList[i] = _blockList[i+1];
		}
		else if (_blockList[i] == block)
		{
#ifdef DEBUG_AXEFX_XL_PLUS_BLOCK_LIST_CONTAINER
	Serial.print( F("AxonAFXXLPBlockListContainer::  found") );
#endif
			found = true;
			_blockList[i] = _blockList[i+1];
			_blockCount--;
#ifdef DEBUG_AXEFX_XL_PLUS_BLOCK_LIST_CONTAINER
	Serial.print( F("AxonAFXXLPBlockListContainer::  and reduce block count (") );
	Serial.print( _blockCount );
	Serial.println( F(")") );
#endif
		}
	}
#ifdef DEBUG_AXEFX_XL_PLUS_BLOCK_LIST_CONTAINER
	Serial.print( F("AxonAFXXLPBlockListContainer::Blocks (") );
	Serial.print( _blockCount );
	Serial.println( F(")") );
#endif
}

AxonAFXXLPBlockContainer *AxonAFXXLPBlockListContainer::getBlock( uint8_t blockNum )
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
