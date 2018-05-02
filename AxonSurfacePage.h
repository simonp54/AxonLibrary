#ifndef AXON_SURFACE_PAGE_h
#define AXON_SURFACE_PAGE_h

#include "AxonSwitchPersistence.h"
#include "Arduino.h"

class AxonSurfacePage
{
  public:
	    AxonSurfacePage() { _contextOK = false; }					// constructor
		uint32_t getSize();
	
		void setBaseAddress( uint32_t baseAddress );

		void format();								// sets the fram totally to zeros
		
//		void setName( const char *name, uint8_t size );
		void build();
		void activate();
		
		AxonSwitchPersistence *switchIndex( uint8_t switchNumber );

		
	protected:
	private:
		static const uint8_t _maxSwitches = 24;			
		static const uint8_t _nameSize = 24;
		
		bool _contextOK = false;
		uint32_t _baseAddress = 0;

		char _name[_nameSize] = { '\0' };
		AxonSwitchPersistence _switchPersistence[_maxSwitches];
		
};

#endif