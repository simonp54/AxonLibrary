/* originally by Simon Peace
 * a wrapper for the genie TouchScreen to provide single access throughtout class model
 * a singleton class
 * VERSION 1.0 10/03/2018
 */

#ifndef AXON_TOUCHSCREEN_h
#define AXON_TOUCHSCREEN_h

#include "genieArduino.h"
#include "AxonContrastType.h"
#include "Arduino.h"

class AxonTouchScreen
{
	public:
		static AxonTouchScreen *instance();							// singleton accessor method
		
		void initialise();
		
		void showTunerScreen();
		void showMainScreen();
		void showAFXXLPPresetNumber();
		void showAFXSceneNumber();
		void showAFXXLPPresetName();
			
		void contrastUp();
		void contrastDown();
		void contrastSet();
		
		void setTunerNote( uint8_t note );
		void setTunerString( uint8_t stringNumber );
		void setTunerData( uint8_t tunerData );
		
	protected:
		AxonTouchScreen();

	private:
		static AxonTouchScreen *_instance;
		
		AxonContrastType _contrast;

		static const uint8_t _RESET_LINE = 4;		// internal parameters

		Genie *_genie = 0;
};

#endif

