/* originally by Simon Peace
 * a wrapper for the genie TouchScreen to provide single access throughtout class model
 * a singleton class
 * VERSION 1.0 10/03/2018
 */

#ifndef AXON_TOUCHSCREEN_h
#define AXON_TOUCHSCREEN_h

#include "genieArduino.h"

class AxonTouchScreen
{
	public:
		static AxonTouchScreen *instance();							// singleton accessor method
		
		void showTunerScreen();
		void showMainScreen();
		void setContrast(uint8_t contrast);
	protected:
		AxonTouchScreen();
	private:
		static AxonTouchScreen *_instance;

		static const uint8_t _RESET_LINE = 4;		// internal parameters

		Genie *_genie = 0;
};

#endif

