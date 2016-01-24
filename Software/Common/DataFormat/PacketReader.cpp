#include "PacketReader.hpp"
#include "helpers.hpp"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

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
		if(!isPacketOkay()) {
			int oldIndex = index;
			reset();
			lookForMissedPackets(oldIndex);
		} else {
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

const char* PacketReader::getPacketData() {
	return &buffer[sizeof(Packetizer::Header)];
}


void PacketReader::fixEndianness() {
	Packetizer::Header* header = getPacketHeader();
	//header->signature = ntohl(header->signature);
	header->length = ntohs(header->length);
	header->packetId = ntohl(header->packetId);
}

bool PacketReader::isHeaderOkay() {
	Packetizer::Header* header = getPacketHeader();
	uint8_t sum = calcCheckSum(0, sizeof(Packetizer::Header));
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

bool PacketReader::isPacketOkay() {
	Packetizer::Header* header = getPacketHeader();
	uint16_t sum = -calcCheckSum(sizeof(Packetizer::Header), sizeof(Packetizer::Header) + header->length);
	uint16_t *checksum = (uint16_t*) &buffer[sizeof(Packetizer::Header) + header->length];
	//printf("%d %d\n", sum, *checksum);
	if(sum != *checksum)
		return false;
	return true;
}

int PacketReader::calcCheckSum(int start, int end) {
	int sum = 0;
	for(int i = start; i < end; ++i)
		sum += (int)buffer[i];
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
