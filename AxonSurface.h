#ifndef AXON_SURFACE_h
#define AXON_SURFACE_h

#include "AxonSurfacePage.h"
#include "Arduino.h"

class AxonSurface
{
  public:
	    AxonSurface() { _contextOK = false; }		// constructor
		
		void format();
		void build();
//		void save();
		void swapPage();

		void setBaseAddress( uint32_t baseAddress );

		uint32_t getSize();

//		uint8_t getPage() { return _currentPage; }

		AxonSurfacePage *page( uint8_t index );

		void setBankSize( uint8_t bankSize ) { _bankSize = constrain( bankSize, 0, 20 ); }
		uint8_t getBankSize() { return _bankSize; }
	protected:
	private:
		static const uint8_t _maxPages = 2;
		
		bool _contextOK = false;

		uint32_t _baseAddress = 0;
		uint8_t _currentPage = 0;
		uint8_t _bankSize = 0;
//		uint8_t _currentSongNumber = 0;
		AxonSurfacePage _page[_maxPages];
};

#endif