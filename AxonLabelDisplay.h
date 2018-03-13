/*
 * AxonLabelDisplay - an object that watches a software switch events... and draws on or off on a specified screen
 */
#ifndef AXON_LABELDISPLAY_h
#define AXON_LABELDISPLAY_h

#include "AxonEventClient.h"
#include "AxonScribble.h" 

class AxonLabelDisplay : public AxonEventClient
{
	public:
		AxonLabelDisplay( uint8_t screenNumber, const char *onLabel, const char *offLabel );
		void setOnLabel( const char *label );
		void setOffLabel( const char *label );
	
		void event( AxonEvent *event );
	private:
		uint8_t _row = 0xFF;
		uint8_t _col = 0xFF;
		char _onLabel[6] = {0};
		char _offLabel[6] = {0};
		
		u8g2_uint_t _w;

};

#endif