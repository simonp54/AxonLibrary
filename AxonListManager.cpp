#include "AxonListManager.h"
#include "AxonStorage.h"

#include "AxonDebugDefines.h"
#include "AxonCheckMem.h"

AxonListManager *AxonListManager::_instance = 0;

AxonListManager *AxonListManager::instance()
{
	if (!_instance)
	{
		_instance = new AxonListManager();
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
	}
	return _instance;
}

/*
 *  CONSTRUCTOR FOR CLASS
 */
AxonListManager::AxonListManager()
{
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
#ifdef DEBUG_LISTS
	Serial.println( F("AxonListManager::ctor") );
#endif
}

void AxonListManager::formatList( uint8_t listNumber = 0 )
{
	uint8_t tmpList = constrain( listNumber, 0, _maxScribbleStripLists - 1 );

	AxonStorage::instance()->format( _baseAddress + (tmpList * (_maxScribbleStripListItems * _scribbleListItemSize)), 0x00, (_maxScribbleStripListItems * _scribbleListItemSize) );
}


const char *AxonListManager::getScribbleStripListItem( uint8_t listNumber = 0, uint8_t listIndex = 0 )
{
	char tmpStr[_scribbleListItemSize+1] = {0};
	uint8_t tmpList = constrain( listNumber, 0, _maxScribbleStripLists - 1 );
	uint8_t tmpItem = constrain( listIndex, 0, _maxScribbleStripListItems - 1 );
	
	AxonStorage::instance()->read( _baseAddress + (tmpList * (_maxScribbleStripListItems * _scribbleListItemSize)) + (tmpItem * _scribbleListItemSize), &tmpStr, _scribbleListItemSize );
	tmpStr[_scribbleListItemSize] = '\0';
	return tmpStr;
}

void AxonListManager::setScribbleStripListItem( uint8_t listNumber = 0, uint8_t listIndex = 0, const char *name = "EMPTY", uint8_t nameSize = _scribbleListItemSize )
{
	uint8_t tmpList = constrain( listNumber, 0, _maxScribbleStripLists - 1 );
	uint8_t tmpItem = constrain( listIndex, 0, _maxScribbleStripListItems - 1 );
	
	AxonStorage::instance()->write( _baseAddress + (tmpList * (_maxScribbleStripListItems * _scribbleListItemSize)) + (tmpItem * _scribbleListItemSize), name, constrain( nameSize, 1, _scribbleListItemSize) );
}