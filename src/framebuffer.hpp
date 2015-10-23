#ifndef _FRAMEBUFFER_HPP_
#define _FRAMEBUFFER_HPP_

#include <stdint.h>
#include "image.hpp"

class Framebuffer{
	private:
		static const uint32_t height = 64;
		static const uint32_t width = 128;
		uint8_t framebuffer[width*height/8];
		
		uint32_t sizeLimit(uint32_t val, uint32_t maxval, uint32_t range);
	public:
		Framebuffer();
		uint8_t *getImage();
		void setPixel(uint32_t x, uint32_t y, bool set);
		void setPixel(uint32_t x, uint32_t y);
		void clearPixel(uint32_t x, uint32_t y);
		void drawImage(uint32_t x, uint32_t y, const Image &image);
};

#endif
