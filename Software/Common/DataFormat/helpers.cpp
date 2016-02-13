/*
 * This file is part of MobilECG, an open source clinical grade Holter
 * ECG. For more information visit http://mobilecg.hu
 *
 * Copyright (C) 2016  Peter Isza, Robert Csordas
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
  #if BYTE_ORDER == BIG_ENDIAN
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
  #if BYTE_ORDER == BIG_ENDIAN
	return x;
  #else // LITTLE_ENDIAN
	return   x << 8 & 0xFF00
		   | x >> 8 & 0x00FF;
  #endif
};
