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
 
#include "framebuffer.hpp"
#include <cstring>

Framebuffer::Framebuffer(){
	clear();
}

uint8_t *Framebuffer::getImage(){
	return framebuffer;
}

void Framebuffer::setPixel(uint32_t x, uint32_t y, bool set){
	if (set)
		framebuffer[x + ((y & 0xF8)<<4)] |= 1 << (y & 7);
	else
		framebuffer[x + ((y & 0xF8)<<4)] &= ~(1 << (y & 7));
}

void Framebuffer::setPixel(uint32_t x, uint32_t y){
	setPixel(x,y,true);
}

void Framebuffer::clearPixel(uint32_t x, uint32_t y){
	setPixel(x,y,false);
}

uint32_t Framebuffer::sizeLimit(uint32_t val, uint32_t maxval, uint32_t range){
	if (val+range > maxval)
		return maxval-val;
	else
		return range;
}

void Framebuffer::drawImage(uint32_t x, uint32_t y, const Image &image){
	uint32_t w = sizeLimit(x, width, image.width);
	uint32_t h = sizeLimit(y, height, image.height);
	
	if (x>=width || y>=height || w<1 || h<1)
		return;
	
	for (uint32_t d_x=0; d_x<w; d_x++){
		for (uint32_t d_y=0; d_y<h; d_y++){
			setPixel(x+d_x, y+d_y, image.getPixel(d_x, d_y));
		}
	}
}

void Framebuffer::clear(){
	uint64_t *fb=(uint64_t*)framebuffer;
	for (int a=0; a<128; a++)
		fb[a]=0;
}

void Framebuffer::vLine(uint32_t x, uint32_t startY, uint32_t stopY){
	if (startY > stopY){
		uint32_t tmp=stopY;
		stopY=startY;
		startY=tmp;
	}
	
	uint8_t d = stopY - startY + 1;
	uint32_t addr=x + ((startY & 0xF8)<<4);
	const uint8_t o = startY & 7;
	
	if (d > (8-o)){
		framebuffer[addr] |= 0xFF << o;
		addr+=width;
		d -= 8-o;
	} else {
		framebuffer[addr] |= (0xFF << o) & (0xFF >> (8-o-d));
		return;
	}
	
	for (; d>8; d-=8){
		framebuffer[addr] = 0xFF;
		addr+=width;
	}
	
	if (d){
		framebuffer[addr] |= (0xFF >> (8-d));
	}
}
