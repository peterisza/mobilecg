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
