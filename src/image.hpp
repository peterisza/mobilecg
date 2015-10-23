#ifndef _IMAGE_HPP_
#define _IMAGE_HPP_

#include <stdint.h>

class Image{
	public:
		enum Order {ROW_CONTINOUS, COL_CONTINOUS};
		enum XDirection {X_NORMAL, X_INVERT};
		enum YDirection {Y_NORMAL, Y_INVERT};
		Image();
		Image(uint8_t *_data, uint32_t _width, uint32_t _height, Order _bitOrder=ROW_CONTINOUS, XDirection _xdir=X_NORMAL, YDirection _ydir=Y_NORMAL, uint32_t _stride=0);
		uint32_t height;
		uint32_t width;
		uint32_t stride;
		const uint8_t *data;
		Order bitOrder;
		XDirection xdir;
		YDirection ydir;
		
		bool getPixel(uint32_t x, uint32_t y) const;
};

#endif
