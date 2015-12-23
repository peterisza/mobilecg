#ifndef _FIFO_BUFFER_HPP
#define _FIFO_BUFFER_HPP

#include <stdint.h>

/* Endian-safe FIFO ring buffer for binary streams. */

namespace ecg {

class BitFifo {
	public:
		BitFifo(char *buffer, int sizeBytes);
		
		#ifndef EMBEDDED
		/* TODO: constructor with dynamic memory allocation. */
		#endif
				
		bool pushByte(uint8_t data);
		bool pushBits(uint32_t data, char numBits);
		
		uint8_t popByte();
		uint32_t popBits(char numBits);
		
		int popBytes(char *buffer, int size);
		int pushBytes(const char *buffer, int size);
		
		int getFreeBytes();
		int getFreeBits();
		
		int getAvailableBytes();
		int getAvailableBits();
		
		int getSizeBytes();
		
	private:
		char *buffer;
		int sizeBytes;
		int sizeBits; 
		int start; // bits
		int end; // bits
};

}

#endif
