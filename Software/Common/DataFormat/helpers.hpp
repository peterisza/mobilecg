#ifndef _HELPERS_HPP
#define _HELPERS_HPP

#include <stdint.h>

uint32_t htonl(uint32_t x);
uint16_t htons(uint16_t x);
uint32_t ntohl(uint32_t x);
uint16_t ntohs(uint16_t x);

class BigEndianInt16
{
	int16_t rep;        

public: 
	BigEndianInt16() { }
	BigEndianInt16(int16_t i) : rep(htons(i)) { }
	operator int16_t() const { return ntohs(rep); }
};

#endif
