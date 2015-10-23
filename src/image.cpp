#include "image.hpp"

Image::Image(){
	
}

Image::Image(const uint8_t *_data, uint32_t _width, uint32_t _height, Order _bitOrder, XDirection _xdir, YDirection _ydir, uint32_t _stride){
	this->data=_data;
	this->width=_width;
	this->height=_height;
	this->stride = _stride ? _stride : (_bitOrder == ROW_CONTINOUS ? _width : _height);
	this->bitOrder = _bitOrder;
	this->xdir = _xdir;
	this->ydir = _ydir;
}

bool Image::getPixel(uint32_t x, uint32_t y) const{
	if (xdir == X_INVERT)
		x = width - x;
	if (ydir == Y_INVERT)
		y = height - y;
	
	uint32_t bitIndex = bitOrder == ROW_CONTINOUS ? y*stride+x : x*stride+y;
	return (data[bitIndex >> 3] >> (bitIndex & 7)) & 1;
}