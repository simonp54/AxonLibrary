#ifndef AXON_SURFACE_MANAGER_h
#define AXON_SURFACE_MANAGER_h

#include "AxonSurface.h"
#include "Arduino.h"

class AxonSurfaceManager
{
  public:
		static AxonSurfaceManager *instance();
		
		void format();
		
		AxonSurface *surface( uint8_t slotNumber );
		
	protected:
	    AxonSurfaceManager();							// constructor
	private:
		uint32_t getSize();

		static AxonSurfaceManager *_instance;

		static const uint8_t _maxSurfaces = 16;
		
		static const uint32_t _baseAddress = 0x10000;
		
		uint8_t _slotNumber = 0;
		
		AxonSurface _surface;	
};

#endif