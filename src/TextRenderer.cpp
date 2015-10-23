#include "TextRenderer.hpp"
#include "font5x8.hpp"
#include <cstring>
#include "image.hpp"

TextRenderer::TextRenderer(Framebuffer &_fb){
	this->fb = &_fb;
	setFont(&font5x8);
	setSpacing(1);
}

void TextRenderer::setFont(Font *_font){
	this->font = _font;

	charImage=Image(NULL, font->w, font->h, font->bitOrder, font->xdir, font->ydir);
}

void TextRenderer::setSpacing(uint32_t _hSpacing){
	this->hSpacing = _hSpacing;
}

void TextRenderer::render(uint32_t x, uint32_t y, const std::string &str){
	render(x,y,str.c_str());
}

void TextRenderer::render(uint32_t x, uint32_t y, const char *str){
	
	for (int c = 0; str[c]; c++){
		charImage.data = &font->data[font->bytesPerChar * str[c]];
		fb -> drawImage(x, y, charImage);
		
		x += font->w+hSpacing;
	}
}
