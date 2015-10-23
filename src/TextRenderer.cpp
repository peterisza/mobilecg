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
	
	render(x,y,buffer);
}
