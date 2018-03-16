#ifndef AXONFASPRESETBLOCKSDATAEVENT_h
#define AXONFASPRESETBLOCKSDATAEVENT_h

#include "AxonFASEvent.h"
#include "AxonAxeFXXLPlusBlockListContainer.h"
#include "AxonEvent.h"

class AxonFASPresetBlocksDataEvent: public AxonFASEvent
{
	public:
		AxonFASPresetBlocksDataEvent( );
		
		void setBlockList( AxonAxeFXXLPlusBlockListContainer *blockList );
		AxonAxeFXXLPlusBlockListContainer *getBlockList();

		bool exactMatch( AxonEvent *event );
	protected:
	private:
		AxonAxeFXXLPlusBlockListContainer *_blockList;
};

#endif