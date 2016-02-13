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
 
#include "BitFifo.hpp"

#include <stdio.h>

using namespace ecg;

BitFifo::BitFifo(char *iBuffer, int iSizeBytes, int bitsAlreadyInBuffer):
	buffer(iBuffer),
	sizeBytes(iSizeBytes),
	sizeBits(iSizeBytes*8),
	start(0),
	end(bitsAlreadyInBuffer)
{
}

void BitFifo::reset() {
	start = 0;
	end = 0;
}

int BitFifo::getAvailableBits() {
	if(end >= start)
		return end - start;
	else
		return sizeBits - start + end;
}

int BitFifo::getFreeBits() {
	return sizeBits - getAvailableBits() - 8;
}

int BitFifo::getAvailableBytes() {
	return getAvailableBits() >> 3;
}

int BitFifo::getFreeBytes() {
	return sizeBytes - ((getAvailableBits() + 7) >> 3) - 1;
}

bool BitFifo::pushBits(uint32_t data, char numBits) {
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
			end -= sizeBits;
		data >>= bitsToPush;
		numBits -= bitsToPush;
	}
	
	return true;
}

uint32_t BitFifo::popBits(char numBits) {
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
			start -= sizeBits;
		readBits += bitsToRead;
	}
	
	return result;
}

int32_t BitFifo::popBitsSigned(char numBits) {
	int32_t data = popBits(numBits);
	if(data & (1 << (numBits-1)))
		data |= ~((1 << numBits)-1);
	return data;
}

bool BitFifo::pushByte(uint8_t data) {
	return pushBits(data, 8);
}

uint8_t BitFifo::popByte() {
	return (uint8_t) popBits(8);
}

int BitFifo::getSizeBytes() {
	return sizeBytes;
}

int BitFifo::popBytes(char *iBuffer, int size) {
	if(getAvailableBytes() < size)
		size = getAvailableBytes();
	for(int i = 0; i < size; ++i) {
		iBuffer[i] = popByte();
	}
	return size;
}

int BitFifo::pushBytes(const char *iBuffer, int size) {
	if(getFreeBytes() < size)
		size = getFreeBytes();
	for(int i = 0; i < size; ++i) {
		pushByte(iBuffer[i]);
	}
	return size;
}
