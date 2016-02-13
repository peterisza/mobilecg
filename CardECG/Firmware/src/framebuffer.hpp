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
 
#ifndef _FRAMEBUFFER_HPP_
#define _FRAMEBUFFER_HPP_

#include <stdint.h>
#include "image.hpp"

class Framebuffer{
	public:
		static const int32_t height = 64;
		static const int32_t width = 128;
		
		Framebuffer();
		uint8_t *getImage();
		void setPixel(uint32_t x, uint32_t y, bool set);
		void setPixel(uint32_t x, uint32_t y);
		void clearPixel(uint32_t x, uint32_t y);
		void drawImage(uint32_t x, uint32_t y, const Image &image);
		void vLine(uint32_t x, uint32_t startY, uint32_t stopY);
		void clear();
	private:
		uint8_t framebuffer[width*height/8];
		uint32_t sizeLimit(uint32_t val, uint32_t maxval, uint32_t range);
};

#endif
