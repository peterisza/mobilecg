#ifndef _TEXT_RENDERER_HPP_
#define _TEXT_RENDERER_HPP_

#include "framebuffer.hpp"
#include "font.hpp"
#include <string>

class TextRenderer{
	private:
		Framebuffer *fb;
		Font *font;
		uint32_t hSpacing;
		Image charImage;
	public:
		TextRenderer(Framebuffer &_fb);
		void setFont(Font *_font);
		void setSpacing(uint32_t _hSpacing);
		
		void render(uint32_t x, uint32_t y, const std::string &str);
		void render(uint32_t x, uint32_t y, const char *str);
};

#endif
