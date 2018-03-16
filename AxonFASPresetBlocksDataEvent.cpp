#include "AxonEventTypeNumbers.h"
#include "AxonFASPresetBlocksDataEvent.h"

#include "AxonDebugDefines.h"

AxonFASPresetBlocksDataEvent::AxonFASPresetBlocksDataEvent( )
{
	_groupID = AXON_FAS_PRESET_BLOCKS_DATA_EVENT_TYPE;
}

void AxonFASPresetBlocksDataEvent::setBlockList( AxonAxeFXXLPlusBlockListContainer *blockList )
{
	_blockList = blockList;
}


AxonAxeFXXLPlusBlockListContainer *AxonFASPresetBlocksDataEvent::getBlockList()
{
	return _blockList;
}


bool AxonFASPresetBlocksDataEvent::exactMatch( AxonEvent *event )
{
#ifdef DEBUG_FAS_FRONT_PANEL_CHANGE_EVENT_TYPE
	Serial.println( F("AxonFASPresetBlocksDataEvent::exactMatch") );
	Serial.println( F("AxonFASPresetBlocksDataEvent::sameType") );
#endif
	return sameType( event );
}