/* originally by Simon Peace
 * object wrapping MIDI library Class
 * VERSION 1.0 08/03/2018
 */
#ifndef AXON_MIDIWRAP_h
#define AXON_MIDIWRAP_h

#include "Arduino.h"

class AxonMidiWrap
{
	public:
		virtual void sendCC( uint8_t channel, uint8_t cc, uint8_t val ) = 0;
		virtual void sendPC( uint8_t channel, uint8_t pc ) = 0;
		virtual void read() = 0;
	protected:
	private:
};

#endif