/* originally by Simon Peace
 * a wrapper for the U8g2Library to provide single access throughtout class model
 * a singleton class
 * VERSION 1.0 22/02/2018
 */

#ifndef AXON_SCRIBBLE_h
#define AXON_SCRIBBLE_h

#include "U8g2lib.h"      // graphics library for scribble screens

class AxonScribble
{
  public:
		static AxonScribble *instance();							// singleton accessor method

		void selectRow( uint8_t row );
		void selectSingle( uint8_t row, uint8_t col );
		void selectAll( );
		
		void centreText( const char *label );
		


		/* u8g2  */

		  
		u8g2_uint_t getDisplayHeight() { return _gfxLib->getDisplayHeight(); }
		u8g2_uint_t getDisplayWidth() { return _gfxLib->getDisplayWidth(); }

		
		/* u8g2_buffer.c */
		void sendBuffer(void) { _gfxLib->sendBuffer(); }
		void clearBuffer(void) { _gfxLib->clearBuffer(); }    
		
		void firstPage(void) { _gfxLib->firstPage(); }
		uint8_t nextPage(void) { return _gfxLib->nextPage(); }
		
		uint8_t *getBufferPtr(void) { return _gfxLib->getBufferPtr(); }
		uint8_t getBufferTileHeight(void) { return _gfxLib->getBufferTileHeight(); }
		uint8_t getBufferTileWidth(void) { return _gfxLib->getBufferTileWidth(); }
		uint8_t getPageCurrTileRow(void) { return _gfxLib->getBufferCurrTileRow(); }	// obsolete
		void setPageCurrTileRow(uint8_t row) { _gfxLib->setBufferCurrTileRow(row); }	// obsolete
		uint8_t getBufferCurrTileRow(void) { return _gfxLib->getBufferCurrTileRow(); }
		void setBufferCurrTileRow(uint8_t row) { _gfxLib->setBufferCurrTileRow(row); }
		
		// this should be renamed to setBufferAutoClear
		void setAutoPageClear(uint8_t mode)  { _gfxLib->setAutoPageClear(mode); }

		/* clib/u8g2.hvline.c */
		void setDrawColor(uint8_t color_index) { _gfxLib->setDrawColor(color_index); }
		uint8_t getDrawColor(void) { return _gfxLib->getDrawColor(); }
		void drawPixel(u8g2_uint_t x, u8g2_uint_t y) { _gfxLib->drawPixel(x, y); }
		void drawHLine(u8g2_uint_t x, u8g2_uint_t y, u8g2_uint_t w) { _gfxLib->drawHLine(x, y, w); }
		void drawVLine(u8g2_uint_t x, u8g2_uint_t y, u8g2_uint_t h) { _gfxLib->drawVLine(x, y, h); }
		void drawHVLine(u8g2_uint_t x, u8g2_uint_t y, u8g2_uint_t len, uint8_t dir) {
		  _gfxLib->drawHVLine(x, y, len, dir); }
		
		/* u8g2_box.c */
		void drawFrame(u8g2_uint_t x, u8g2_uint_t y, u8g2_uint_t w, u8g2_uint_t h) { _gfxLib->drawFrame(x, y, w, h); }
		void drawRFrame(u8g2_uint_t x, u8g2_uint_t y, u8g2_uint_t w, u8g2_uint_t h, u8g2_uint_t r) { _gfxLib->drawRFrame(x, y, w, h,r); }
		void drawBox(u8g2_uint_t x, u8g2_uint_t y, u8g2_uint_t w, u8g2_uint_t h) { _gfxLib->drawBox(x, y, w, h); }
		void drawRBox(u8g2_uint_t x, u8g2_uint_t y, u8g2_uint_t w, u8g2_uint_t h, u8g2_uint_t r) { _gfxLib->drawRBox(x, y, w, h,r); }
		
		/* u8g2_circle.c */
		void drawCircle(u8g2_uint_t x0, u8g2_uint_t y0, u8g2_uint_t rad, uint8_t opt = U8G2_DRAW_ALL) { _gfxLib->drawCircle(x0, y0, rad, opt); }
		void drawDisc(u8g2_uint_t x0, u8g2_uint_t y0, u8g2_uint_t rad, uint8_t opt = U8G2_DRAW_ALL) { _gfxLib->drawDisc(x0, y0, rad, opt); }     
		void drawEllipse(u8g2_uint_t x0, u8g2_uint_t y0, u8g2_uint_t rx, u8g2_uint_t ry, uint8_t opt = U8G2_DRAW_ALL) { _gfxLib->drawEllipse(x0, y0, rx, ry, opt); }
		void drawFilledEllipse(u8g2_uint_t x0, u8g2_uint_t y0, u8g2_uint_t rx, u8g2_uint_t ry, uint8_t opt = U8G2_DRAW_ALL) { _gfxLib->drawFilledEllipse(x0, y0, rx, ry, opt); }    

		/* u8g2_line.c */
		void drawLine(u8g2_uint_t x1, u8g2_uint_t y1, u8g2_uint_t x2, u8g2_uint_t y2) 
		  { _gfxLib->drawLine(x1, y1, x2, y2); }

		/* u8g2_bitmap.c */
		void setBitmapMode(uint8_t is_transparent) 
		  { _gfxLib->setBitmapMode(is_transparent); }
		void drawBitmap(u8g2_uint_t x, u8g2_uint_t y, u8g2_uint_t cnt, u8g2_uint_t h, const uint8_t *bitmap)
		  { _gfxLib->drawBitmap(x, y, cnt, h, bitmap); }
		void drawXBM(u8g2_uint_t x, u8g2_uint_t y, u8g2_uint_t w, u8g2_uint_t h, const uint8_t *bitmap)
		  { _gfxLib->drawXBM(x, y, w, h, bitmap); }
		void drawXBMP(u8g2_uint_t x, u8g2_uint_t y, u8g2_uint_t w, u8g2_uint_t h, const uint8_t *bitmap)
		  { _gfxLib->drawXBMP(x, y, w, h, bitmap); }
		
		
		/* u8g2_polygon.c */
		void drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2) 
		  { _gfxLib->drawTriangle(x0, y0, x1, y1, x2, y2); }
		  
		
		/* u8g2_font.c */

		void setFont(const uint8_t  *font) {_gfxLib->setFont(font); }
		void setFontMode(uint8_t  is_transparent) {_gfxLib->setFontMode(is_transparent); }
		void setFontDirection(uint8_t dir) {_gfxLib->setFontDirection(dir); }

		int8_t getAscent(void) { return _gfxLib->getAscent(); }
		int8_t getDescent(void) { return _gfxLib->getDescent(); }
		
		void setFontPosBaseline(void) { _gfxLib->setFontPosBaseline(); }
		void setFontPosBottom(void) { _gfxLib->setFontPosBottom(); }
		void setFontPosTop(void) { _gfxLib->setFontPosTop(); }
		void setFontPosCenter(void) { _gfxLib->setFontPosCenter(); }

		void setFontRefHeightText(void) { _gfxLib->setFontRefHeightText(); }
		void setFontRefHeightExtendedText(void) { _gfxLib->setFontRefHeightExtendedText(); }
		void setFontRefHeightAll(void) { _gfxLib->setFontRefHeightAll(); }
		

		u8g2_uint_t drawGlyph(u8g2_uint_t x, u8g2_uint_t y, uint16_t encoding) { return _gfxLib->drawGlyph(x, y, encoding); }    
		u8g2_uint_t drawStr(u8g2_uint_t x, u8g2_uint_t y, const char *s) { return _gfxLib->drawStr(x, y, s); }
		u8g2_uint_t drawUTF8(u8g2_uint_t x, u8g2_uint_t y, const char *s) { return _gfxLib->drawUTF8(x, y, s); }
		u8g2_uint_t drawExtUTF8(u8g2_uint_t x, u8g2_uint_t y, uint8_t to_left, const uint16_t *kerning_table, const char *s) 
		  { return _gfxLib->drawExtUTF8(x, y, to_left, kerning_table, s); }

		  
		u8g2_uint_t getStrWidth(const char *s) { return _gfxLib->getStrWidth(s); }
		u8g2_uint_t getUTF8Width(const char *s) { return _gfxLib->getUTF8Width(s); }





	protected:
		AxonScribble();
	private:
		void _deselectDisplay();

		static AxonScribble *_instance;

		static const uint8_t _MUX_ADDR_OFFSET;
		static const uint8_t _ROW_ALL_LSB_MASK = 0xFF;
		static const uint8_t _ROW_NON_LSB_MASK = 0x00;
		static const uint16_t _ALL_ROWS_AND_COLS_MASK = 0x07FF;
		static const uint8_t _ROW1_MSB_MASK = 0x01;
		static const uint8_t _ROW2_MSB_MASK = 0x02;
		static const uint8_t _ROW3_MSB_MASK = 0x04;

		U8G2_SSD1306_128X64_NONAME_F_HW_I2C *_gfxLib = 0;

		uint16_t _scribbleMask = 0x0000;
};

#endif