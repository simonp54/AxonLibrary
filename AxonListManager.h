#ifndef AXON_LIST_MANAGER_h
#define AXON_LIST_MANAGER_h

#include "Arduino.h"

class AxonListManager
{
	private:
		static AxonListManager *_instance;
		
		static const uint32_t _baseAddress = 0x20000;
		static const uint8_t _maxScribbleStripLists = 8;
		static const uint8_t _maxScribbleStripListItems = 128;
		static const uint8_t _scribbleListItemSize = 5;
	public:
		static AxonListManager *instance();
		
		void formatList( uint8_t listNumber = 0 );
		
		const char* getScribbleStripListItem( uint8_t listNumber = 0, uint8_t listIndex = 0 );
		void setScribbleStripListItem( uint8_t listNumber = 0, uint8_t listIndex = 0, const char *name = "EMPTY", uint8_t nameSize = _scribbleListItemSize );
		
	protected:
	    AxonListManager();							// constructor
};

#endif