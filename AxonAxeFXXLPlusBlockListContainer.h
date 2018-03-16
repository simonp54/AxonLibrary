#ifndef AXON_AXEFXXLPLUSBLOCKLISTCONTAINER_h
#define AXON_AXEFXXLPLUSBLOCKLISTCONTAINER_h

#include "AxonAxeFXXLPlusBlockContainer.h"

class AxonAxeFXXLPlusBlockListContainer
{
	public:
		AxonAxeFXXLPlusBlockListContainer();

		void addBlock( AxonAxeFXXLPlusBlockContainer *block );
		void removeBlock( AxonAxeFXXLPlusBlockContainer *block );
		
		AxonAxeFXXLPlusBlockContainer *getBlock( uint8_t blockNum );
	
	protected:
	
	private:
		static const uint8_t _MAX_BLOCKS = 30;
		
		uint8_t _blockCount = 0;
		AxonAxeFXXLPlusBlockContainer *_blockList[_MAX_BLOCKS];		
};

#endif