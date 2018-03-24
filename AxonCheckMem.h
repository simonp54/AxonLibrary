/* originally by Simon Peace
 * a wrapper for "key scanning" driver chip on the Axon
 * VERSION 1.0 28/02/2018
 */

#ifndef AXON_CHECKMEM_h
#define AXON_CHECKMEM_h

#include "Arduino.h"

class AxonCheckMem
{
  public:
		static AxonCheckMem *instance();
				
		void check();							// the servicing routine that needs to be called every time through a program loop
	protected:
	    AxonCheckMem();							// constructor
	private:
		static const uint8_t _QUICKEST_RECHECK_INTERVAL = 1000;
	
		uint64_t _lastCheckMillis;								// throttle timing

		static AxonCheckMem *_instance;
		
		uint16_t _heapmax = 6000, _stackmax = 6000;
		uint16_t _heapmin = 9000, _stackmin = 9000;
		uint8_t *_heapptr, *_stackptr;
};

#endif