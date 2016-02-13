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
 
#ifndef _TEXT_RENDERER_HPP_
#define _TEXT_RENDERER_HPP_

#include "framebuffer.hpp"
#include "font.hpp"
#include <string>

class TextRenderer{
	private:
		Framebuffer *fb;
		const Font *font;
		uint32_t hSpacing;
		uint32_t vSpacing;
		Image charImage;
	public:
		TextRenderer(Framebuffer &_fb);
		void setFont(const Font *_font);
		void setSpacing(uint32_t _hSpacing, uint32_t _vSpacing=1);
		
		void render(uint32_t x, uint32_t y, const char *str);
		void printf(uint32_t x, uint32_t y, const char *format, ...);
		
		enum SpecialCoordinate {
			ALIGN_CENTER = 0x1000,
			ALIGN_RIGHT  = 0x2000,
			ALIGN_LEFT   = 0
		};
};

#endif
