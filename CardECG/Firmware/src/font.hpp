#ifndef _FONT_H_
#define _FONT_H_

#include <stdint.h>
#include "image.hpp"

struct Font{
	const uint8_t *data;
	uint8_t h;
	uint8_t w;
	uint8_t bytesPerChar;
	Image::XDirection xdir;
	Image::YDirection ydir;
	Image::Order bitOrder;
	
	Font(const uint8_t *_data, uint8_t _h, uint8_t _w, uint8_t _bytesPerChar, 
			Image::Order _bitOrder=Image::ROW_CONTINOUS, Image::XDirection _xdir=Image::X_NORMAL, 
			Image::YDirection _ydir=Image::Y_NORMAL){
			
		data=_data;
		h=_h;
		w=_w;
		bytesPerChar=_bytesPerChar;
		
		xdir = _xdir;
		ydir = _ydir;
		bitOrder = _bitOrder;
	}
};

#endif
