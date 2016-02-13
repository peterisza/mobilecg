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
 
#include "PacketReader.hpp"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

//#define DEBUG
#ifdef DEBUG
	#include "log.h"
#endif

PacketReader::PacketReader():
	index(0)
{
	buffer.resize(1000);
}

void PacketReader::addByte(char byte) {
	if(packetReady)
		reset();
		
	if(buffer.size() > MAX_BUFFER_SIZE)
		reset();

	if(
		(index == 1 && buffer[0] != 'D') || 
		(index == 2 && buffer[1] != 'A') ||
		(index == 3 && buffer[2] != 'T') ||
		(index == 4 && buffer[3] != 'A') 
	) {
		reset();
	}
	
	if(buffer.size() <= index)
		buffer.resize(index+1000);
	buffer[index] = byte;
	index++;
	packetReady = false;
	
	if(index == sizeof(Packetizer::Header) && !isHeaderOkay()) {
		int oldIndex = index;
		reset();
		lookForMissedPackets(oldIndex);
	}
	
	if(packetReceived()) {
		#ifdef DEBUG
			LOGD("potential packet, length=%d", index);
		#endif

		if(!isPacketOkay()) {
			#ifdef DEBUG
				LOGD("packet NOT okay");
			#endif
			int oldIndex = index;
			reset();
			lookForMissedPackets(oldIndex);
		} else {
			#ifdef DEBUG
				LOGD("okay");
			#endif
			packetReady = true;
		}	
	}

}

bool PacketReader::isPacketReady() {
	return packetReady;
}

Packetizer::Header* PacketReader::getPacketHeader() {
	return (Packetizer::Header*) buffer.data();
}

char* PacketReader::getPacketData() {
	return &buffer[sizeof(Packetizer::Header)];
}

bool PacketReader::isHeaderOkay() {
	Packetizer::Header* header = getPacketHeader();
	uint8_t sum = calcCheckSum(0, sizeof(Packetizer::Header));

	#ifdef DEBUG
		LOGD("packetId %d sum %d\n", header->packetId, (int)sum);
	#endif

	if(sum != 0)
		return false;
	return true;
}

bool PacketReader::packetReceived() {
	Packetizer::Header* header = getPacketHeader();
	if(index < sizeof(Packetizer::Header))
		return false;
	return index == sizeof(Packetizer::Header) + header->length + 2;
}

static uint8_t pina;
bool PacketReader::isPacketOkay() {
	Packetizer::Header* header = getPacketHeader();
	#ifdef DEBUG
		LOGD("Packet ID: %d", header->packetId);
	#endif
	int *pinalyuk=(int*)(&buffer[sizeof(Packetizer::Header)+5]);
	#ifdef DEBUG
		LOGD("Bits: %d",*pinalyuk);
	#endif
	uint16_t sum = -calcCheckSum(sizeof(Packetizer::Header), sizeof(Packetizer::Header) + header->length);
	uint16_t *checksum = (uint16_t*) &buffer[sizeof(Packetizer::Header) + header->length];
	#ifdef DEBUG
		LOGD("checksum calculated: %d, in packet: %d \n", sum, *checksum);
	#endif
	if(sum != *checksum)
		return false;
	return true;
}

int PacketReader::calcCheckSum(int start, int end) {
	int sum = 0;
	for(int i = start; i < end; ++i)
		sum += (uint8_t)buffer[i];
	return sum;
}

bool PacketReader::isSignatureOkay() {
	Packetizer::Header* header = getPacketHeader();
	if(header->signature != Packetizer::SIGNATURE)
		return false;
	return true;
}

void PacketReader::reset() {
	index = 0;
	packetReady = false;
}

void PacketReader::lookForMissedPackets(int length) {
	for(int i = 1; i < length; ++i)
		addByte(buffer[i]);
}
