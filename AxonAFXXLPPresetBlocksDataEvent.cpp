#include "AxonEventTypeNumbers.h"
#include "AxonAFXXLPPresetBlocksDataEvent.h"

#include "AxonDebugDefines.h"

AxonAFXXLPPresetBlocksDataEvent::AxonAFXXLPPresetBlocksDataEvent( )
{
	_groupID = AXON_FAS_PRESET_BLOCKS_DATA_EVENT_TYPE;
}

void AxonAFXXLPPresetBlocksDataEvent::setBlockList( AxonAFXXLPBlockListContainer *blockList )
{
	_blockList = blockList;
}


AxonAFXXLPBlockListContainer *AxonAFXXLPPresetBlocksDataEvent::getBlockList()
{
	return _blockList;
}


bool AxonAFXXLPPresetBlocksDataEvent::exactMatch( AxonEvent *event )
{
#ifdef DEBUG_FAS_FRONT_PANEL_CHANGE_EVENT_TYPE
	Serial.println( F("AxonAFXXLPPresetBlocksDataEvent::exactMatch") );
	Serial.println( F("AxonAFXXLPPresetBlocksDataEvent::sameType") );
#endif
	return sameType( event );
}