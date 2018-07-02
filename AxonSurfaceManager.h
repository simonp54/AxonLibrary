#ifndef AXON_SURFACE_MANAGER_h
#define AXON_SURFACE_MANAGER_h

#include "Arduino.h"
#include "AxonLogicBlock.h"

class AxonSurfaceManager
{
	public:
		static const uint8_t maxSurfaceItems = 32;
		static const uint8_t hardwareInterfacesPerSystem = 26;
		
	private:
		static const uint8_t _mapHardwareInterface[];

		static AxonSurfaceManager *_instance;
		
		static const uint32_t _baseAddress = 0x58000;
		
		uint8_t _qSurfaceNumber = 0;
		bool _surfaceQueued = false;

		uint8_t _currentSurfaceNumber = 1;
		
		AxonLogicBlock *_logicBlockList[hardwareInterfacesPerSystem] = { NULL };
		
		void dropAllLogicBlocks();
		
	public:
		static const uint8_t NO_ERROR;
		static const uint8_t INVALID_SURFACE_NUMBER;
		static const uint8_t UNABLE_TO_WRITE;
		static const uint8_t UNABLE_TO_READ;
		

		static AxonSurfaceManager *instance();
		
		bool itemOutstanding() { return(_surfaceQueued); }
		void processOutstanding();
		
		void format();

		struct AxonSurfaceInfo_t
		{
			uint16_t hardwareInterface[hardwareInterfacesPerSystem];
		};
		
		uint8_t defineSurface( uint8_t surfaceNumber, const AxonSurfaceInfo_t *surfaceInfo );
		uint8_t getSurfaceBuffer( uint8_t surfaceNumber, AxonSurfaceInfo_t *surfaceInfo );
		
		void qSurface( uint8_t surfaceNumber );
		
		uint8_t getSurfaceNumber() { return _currentSurfaceNumber; }
		
		void __REMOVE__check_written( uint8_t surfaceNumber );
	protected:
	    AxonSurfaceManager();							// constructor
		void loadSurface( uint8_t surfaceNumber );
};

#endif