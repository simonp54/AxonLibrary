#ifndef AXON_SURFACE_MANAGER_h
#define AXON_SURFACE_MANAGER_h

#include "Arduino.h"
#include "AxonLogicBlock.h"

class AxonSurfaceManager
{
	public:
		static const uint8_t hardwareInterfacesPerSystem = 26;
	private:
		static AxonSurfaceManager *_instance;
		
		static const uint32_t _baseAddress = 0x5A800;
		static const uint16_t _maxSurfaceItems = 32;
		
		AxonLogicBlock *_logicBlockList[hardwareInterfacesPerSystem] = { NULL };
		
		void dropAllLogicBlocks();
//		void dropAllDisplayBlocks();
		
	public:
		static const uint8_t NO_ERROR;
		static const uint8_t INVALID_SURFACE_NUMBER;
		static const uint8_t UNABLE_TO_WRITE;
		static const uint8_t UNABLE_TO_READ;
		

		static AxonSurfaceManager *instance();
		
		void format();

		struct AxonSurfaceInfo_t
		{
			uint16_t hardwareInterface[hardwareInterfacesPerSystem];
		};
		
		uint8_t defineSurface( uint16_t surfaceNumber, const AxonSurfaceInfo_t *surfaceInfo );
		uint8_t getSurfaceBuffer( uint16_t surfaceNumber, AxonSurfaceInfo_t *surfaceInfo );
		
		void loadSurface( uint16_t surfaceNumber );
		
		void __REMOVE__check_written( uint16_t surfaceNumber );
	protected:
	    AxonSurfaceManager();							// constructor
};

#endif