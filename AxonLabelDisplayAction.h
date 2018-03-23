/*
 * AxonLabelDisplayAction - an object that watches a software switch events... and draws on or off on a specified screen
 */
#ifndef AXON_LABEL_DISPLAY_ACTION_h
#define AXON_LABEL_DISPLAY_ACTION_h

#include "AxonAction.h"
#include "AxonScribble.h" 
#include "AxonSoftwareSwitchEvent.h"

class AxonLabelDisplayAction : public AxonAction
{
	public:
		AxonLabelDisplayAction( uint8_t screenNumber, const char *onLabel, const char *offLabel );
		~AxonLabelDisplayAction();
		void setOnLabel( const char *label );
		void setOffLabel( const char *label );
	
		void execute( AxonAction *sender, AxonEvent *event );
	private:
		uint8_t _row = 0xFF;
		uint8_t _col = 0xFF;
		char _onLabel[6] = {0};
		char _offLabel[6] = {0};
		
		u8g2_uint_t _w;
};

#endif