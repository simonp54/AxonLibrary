#ifndef AXONFASPRESETBLOCKSDATAEVENT_h
#define AXONFASPRESETBLOCKSDATAEVENT_h

#include "AxonAFXXLPEvent.h"
#include "AxonAFXXLPBlockListContainer.h"
#include "AxonEvent.h"

class AxonAFXXLPPresetBlocksDataEvent: public AxonAFXXLPEvent
{
	public:
		AxonAFXXLPPresetBlocksDataEvent( );
		
		void setBlockList( AxonAFXXLPBlockListContainer *blockList );
		AxonAFXXLPBlockListContainer *getBlockList();

		bool exactMatch( AxonEvent *event );
	protected:
	private:
		AxonAFXXLPBlockListContainer *_blockList;
};

#endif