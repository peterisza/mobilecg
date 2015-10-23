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
};

#endif
