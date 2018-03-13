/* originally by Simon Peace
 * a wrapper for the U8g2Library to provide single access throughtout class model
 * a singleton class
 * VERSION 1.0 22/02/2018
 */

#include "Arduino.h"
#include "AxonScribble.h"
#include "Wire.h"
#include "U8g2lib.h"      // graphics library for scribble screens

//#define AXONSCRIBBLE_DEBUG
AxonScribble *AxonScribble::_instance = 0;
const uint8_t AxonScribble::_MUX_ADDR_OFFSET = 0x70;

AxonScribble *AxonScribble::instance()
{
	if (!_instance)
	{
		_instance = new AxonScribble();
	}
	return _instance;
}

/*
 *  CONSTRUCTOR FOR CLASS
 */
AxonScribble::AxonScribble()
{
	if (TWCR == 0) // do this check so that Wire only gets initialized once
	{
		Wire.begin();
	}

	_gfxLib = new U8G2_SSD1306_128X64_NONAME_F_HW_I2C(U8G2_R0, SCL, SDA, U8X8_PIN_NONE);

	selectAll();

	_gfxLib->begin();
//	_gfxLib->clearBuffer();
//	_gfxLib->sendBuffer();
	centreText( "Axon" );
	
	_deselectDisplay();
}

void AxonScribble::selectRow( uint8_t row )
{
	_deselectDisplay();		// deselect any previous row enabled screens
	if ( (row < 1) || (row > 3) )
	{
		return;				// row out of bounds
	}

	_scribbleMask = ((0x01 << (row - 1))<<8) | _ROW_ALL_LSB_MASK;
	
	Wire.beginTransmission( _MUX_ADDR_OFFSET + row );
	Wire.write(_ROW_ALL_LSB_MASK);
	Wire.endTransmission();
}

void AxonScribble::selectSingle( uint8_t row, uint8_t col )
{
	_deselectDisplay();		// deselect any previous row enabled screens
	if ( ((col < 1) || (col > 8)) || ((row < 1) || (row > 3)) )
	{
		return;				// column or row out of bounds
	}

	_scribbleMask = ((0x01 << (row - 1))<<8) | (0x01 << (col - 1));
	
	Wire.beginTransmission( _MUX_ADDR_OFFSET + row );
	Wire.write(0x01 << (col-1));
	Wire.endTransmission();
}

void AxonScribble::selectAll( )
{
	_scribbleMask = _ALL_ROWS_AND_COLS_MASK;
	
	Wire.beginTransmission( _MUX_ADDR_OFFSET + 1 );
	Wire.write(_ROW_ALL_LSB_MASK);
	Wire.endTransmission();

	Wire.beginTransmission( _MUX_ADDR_OFFSET + 2 );
	Wire.write(_ROW_ALL_LSB_MASK);
	Wire.endTransmission();

	Wire.beginTransmission( _MUX_ADDR_OFFSET + 3 );
	Wire.write(_ROW_ALL_LSB_MASK);
	Wire.endTransmission();
}

void AxonScribble::_deselectDisplay()
{
	if ( ((_scribbleMask >> 8) & _ROW1_MSB_MASK) == _ROW1_MSB_MASK)
	{
		Wire.beginTransmission( _MUX_ADDR_OFFSET + 1 );
		Wire.write( _ROW_NON_LSB_MASK );
		Wire.endTransmission();
	}
	if ( ((_scribbleMask >> 8) & _ROW2_MSB_MASK) == _ROW2_MSB_MASK)
	{
		Wire.beginTransmission( _MUX_ADDR_OFFSET + 2 );
		Wire.write( _ROW_NON_LSB_MASK );
		Wire.endTransmission();
	}
	if ( ((_scribbleMask >> 8) & _ROW3_MSB_MASK) == _ROW3_MSB_MASK)
	{
		Wire.beginTransmission( _MUX_ADDR_OFFSET + 3 );
		Wire.write( _ROW_NON_LSB_MASK );
		Wire.endTransmission();
	}
}

void AxonScribble::centreText( const char *label )
{
	_gfxLib->clearBuffer();          // clear the internal memory
	_gfxLib->setFont(u8g_font_helvR24); // choose a suitable font
	_gfxLib->setFontPosBaseline();
	_gfxLib->setFontRefHeightText();
	
	u8g2_uint_t w = _gfxLib->getStrWidth(label);
	u8g2_uint_t h = _gfxLib->getAscent();
	_gfxLib->drawStr((_gfxLib->getDisplayWidth()>>1)-(w>>1),
					 (_gfxLib->getDisplayHeight()>>1)+(h>>1), label); // write something to the internal memory
	_gfxLib->sendBuffer();          // transfer internal memory to the display
}