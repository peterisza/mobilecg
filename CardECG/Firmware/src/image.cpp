/*
 * This file is part of MobilECG, an open source clinical grade Holter
 * ECG. For more information visit http://mobilecg.hu
 *
 * Copyright (C) 2016  Robert Csordas, Peter Isza
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
 
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