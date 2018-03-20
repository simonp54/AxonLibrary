#ifndef AXON_AXEFXXLPLUSBLOCKLISTCONTAINER_h
#define AXON_AXEFXXLPLUSBLOCKLISTCONTAINER_h

#include "AxonAFXXLPBlockContainer.h"

class AxonAFXXLPBlockListContainer
{
	public:
		AxonAFXXLPBlockListContainer();
		~AxonAFXXLPBlockListContainer();

		void addBlock( AxonAFXXLPBlockContainer *block );
		void removeBlock( AxonAFXXLPBlockContainer *block );
		
		AxonAFXXLPBlockContainer *getBlock( uint8_t blockNum );
	
	protected:
	
	private:
		static const uint8_t _MAX_BLOCKS = 30;
		
		uint8_t _blockCount = 0;
		AxonAFXXLPBlockContainer *_blockList[_MAX_BLOCKS];		
};

#endif