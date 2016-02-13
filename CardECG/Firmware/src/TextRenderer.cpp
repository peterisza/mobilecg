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
 
#include "TextRenderer.hpp"
#include "font5x8.hpp"
#include <cstring>
#include <stdarg.h>
#include "printf.hpp"
#include "image.hpp"

TextRenderer::TextRenderer(Framebuffer &_fb){
	this->fb = &_fb;
	setFont(&font5x8);
	setSpacing(1);
}

void TextRenderer::setFont(const Font *_font){
	this->font = _font;

	charImage=Image(NULL, font->w, font->h, font->bitOrder, font->xdir, font->ydir);
}

void TextRenderer::setSpacing(uint32_t _hSpacing, uint32_t _vSpacing){
	this->hSpacing = _hSpacing;
	this->vSpacing = _vSpacing;
}


void TextRenderer::render(uint32_t x, uint32_t y, const char *str){
	uint32_t startX=x;
	
	for (int c = 0; str[c]; c++){
		if (str[c]=='\n'){
			y += font->h + vSpacing;
			x = startX;
			continue;
		}
		
		charImage.data = &font->data[font->bytesPerChar * str[c]];
		fb -> drawImage(x, y, charImage);
		
		x += font->w+hSpacing;
	}
}

void TextRenderer::printf(uint32_t x, uint32_t y, const char *format, ...){
	char buffer[64];
	
	va_list vl;
	va_start(vl, format);
	vsnprintf(buffer, sizeof(buffer), format, vl);
	va_end(vl);
	
	if(x & ALIGN_CENTER)
		x -= (font->w + hSpacing) * strlen(buffer) / 2; 

	if(x & ALIGN_RIGHT)
		x -= (font->w + hSpacing) * strlen(buffer); 
		
	x &= 0xFFF;
		
	render(x,y,buffer);
}

