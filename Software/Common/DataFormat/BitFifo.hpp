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
 
#ifndef _FIFO_BUFFER_HPP
#define _FIFO_BUFFER_HPP

#include <stdint.h>

/* Endian-safe FIFO ring buffer for binary streams. */

namespace ecg {

class BitFifo {
	public:
		BitFifo(char *buffer, int sizeBytes, int bitsAlreadyInBuffer=0);
		
		#ifndef EMBEDDED
		/* TODO: constructor with dynamic memory allocation. */
		#endif
				
		bool pushByte(uint8_t data);
		bool pushBits(uint32_t data, char numBits);
		
		uint8_t popByte();
		uint32_t popBits(char numBits);
		int32_t popBitsSigned(char numBits);
		
		int popBytes(char *buffer, int size);
		int pushBytes(const char *buffer, int size);
		
		int getFreeBytes();
		int getFreeBits();
		
		int getAvailableBytes();
		int getAvailableBits();
		
		int getSizeBytes();
		
		void reset();
		
	private:
		char *buffer;
		int sizeBytes;
		int sizeBits; 
		int start; // bits
		int end; // bits
};

}

#endif
