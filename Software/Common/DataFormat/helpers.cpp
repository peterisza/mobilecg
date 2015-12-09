#include "helpers.hpp"

uint32_t htonl(uint32_t x) 
{
  #if BYTE_ORDER == BIG_ENDIAN
	return x;
  #else // LITTLE_ENDIAN
	return   x << 24 & 0xFF000000
		   | x <<  8 & 0x00FF0000
		   | x >>  8 & 0x0000FF00
		   | x >> 24 & 0x000000FF;
  #endif
};

uint16_t htons(uint16_t x)
{
  #if BYTE_ORDER == BIG_ENDIAN
	return x;
  #else // LITTLE_ENDIAN
	return   x << 8 & 0xFF00
		   | x >> 8 & 0x00FF;
  #endif
};

uint32_t ntohl(uint32_t x) 
{
  #if BYTE_ORDER != BIG_ENDIAN
	return x;
  #else // LITTLE_ENDIAN
	return   x << 24 & 0xFF000000
		   | x <<  8 & 0x00FF0000
		   | x >>  8 & 0x0000FF00
		   | x >> 24 & 0x000000FF;
  #endif
};

uint16_t ntohs(uint16_t x)
{
  #if BYTE_ORDER != BIG_ENDIAN
	return x;
  #else // LITTLE_ENDIAN
	return   x << 8 & 0xFF00
		   | x >> 8 & 0x00FF;
  #endif
};
