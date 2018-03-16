#ifndef AXON_FASMANUFACTURERDECODER_h
#define AXON_FASMANUFACTURERDECODER_h

#include "Arduino.h"
#include "AxonSysExDecoder.h"

class AxonFASManufacturerDecoder: public AxonSysExDecoder
{
	public:
		AxonFASManufacturerDecoder();
		
		virtual bool decode( AxonSysExMidiEvent *event );
	protected:

};

#endif