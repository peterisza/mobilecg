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
 
#ifndef _IMAGE_HPP_
#define _IMAGE_HPP_

#include <stdint.h>

class Image{
	public:
		enum Order {ROW_CONTINOUS, COL_CONTINOUS};
		enum XDirection {X_NORMAL, X_INVERT};
		enum YDirection {Y_NORMAL, Y_INVERT};
		Image();
		Image(const uint8_t *_data, uint32_t _width, uint32_t _height, Order _bitOrder=ROW_CONTINOUS, XDirection _xdir=X_NORMAL, YDirection _ydir=Y_NORMAL, uint32_t _stride=0);
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
