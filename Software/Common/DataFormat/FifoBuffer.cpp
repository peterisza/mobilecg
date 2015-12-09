#include "FifoBuffer.hpp"

#include <stdio.h>

using namespace ecg;

FifoBuffer::FifoBuffer(char *buffer, int sizeBytes):
	buffer(buffer),
	sizeBytes(sizeBytes),
	sizeBits(sizeBytes*8),
	start(0),
	end(0)
{
}

int FifoBuffer::getAvailableBits() {
	if(end >= start)
		return end - start;
	else
		return sizeBits - start + end;
}

int FifoBuffer::getFreeBits() {
	return sizeBits - getAvailableBits() - 8;
}

int FifoBuffer::getAvailableBytes() {
	return getAvailableBits() >> 3;
}

int FifoBuffer::getFreeBytes() {
	return sizeBytes - ((getAvailableBits() + 7) >> 3) - 1;
}

bool FifoBuffer::pushBits(uint32_t data, char numBits) {
	if(getFreeBits() < numBits)
		return false;
	
	while(numBits > 0) {
		int bitsInCurrentByte = end & 7;
		int bitsToPush = 8 - bitsInCurrentByte;
		if(numBits < bitsToPush)
			bitsToPush = numBits;
			
		if(bitsInCurrentByte == 0)
			buffer[end >> 3] = 0;			
		buffer[end >> 3] |= (data & ((1 << bitsToPush) - 1)) << bitsInCurrentByte;
		end += bitsToPush;
		if(end >= sizeBits)
			end = 0;
		data >>= bitsToPush;
		numBits -= bitsToPush;
		//printf("Pushed %d bits, start: %d, end: %d.\n", bitsToPush, start, end);	
	}

	/*for(int i = 0; i < sizeBits; ++i)
		printf("%d", buffer[i >> 3] & (1 << (i&7)) ? 1 : 0);
		
	printf("\n");*/
	
	return true;
}

uint32_t FifoBuffer::popBits(char numBits) {
	if(getAvailableBits() < numBits)
		return 0;
	
	uint32_t result = 0;
	
	int readBits = 0;
	while (readBits < numBits) {
		int bitsToRead = 8 - (start & 7);
		if(readBits + bitsToRead > numBits)
			bitsToRead = numBits - readBits;
		result |= ((buffer[start >> 3] >> (start & 7)) & ((1 << bitsToRead)-1)) << readBits;
		start += bitsToRead;
		if(start >= sizeBits)
			start = 0;
		readBits += bitsToRead;
		//printf("Read %d bits, start: %d, end: %d.\n", bitsToRead, start, end);		
	}
	
	return result;
}

bool FifoBuffer::pushByte(uint8_t data) {
	return pushBits(data, 8);
}

uint8_t FifoBuffer::popByte() {
	return (uint8_t) popBits(8);
}

int FifoBuffer::getSizeBytes() {
	return sizeBytes;
}

int FifoBuffer::popBytes(char *buffer, int size) {
	if(getAvailableBytes() < size)
		size = getAvailableBytes();
	for(int i = 0; i < size; ++i) {
		buffer[i] = popByte();
	}
	return size;
}

int FifoBuffer::pushBytes(const char *buffer, int size) {
	if(getFreeBytes() < size)
		size = getFreeBytes();
	for(int i = 0; i < size; ++i) {
		pushByte(buffer[i]);
	}
	return size;
}
