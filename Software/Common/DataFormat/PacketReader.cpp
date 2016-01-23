#include "PacketReader.hpp"
#include "helpers.hpp"

#include <stdint.h>

PacketReader::PacketReader():
	index(0)
{
	buffer.resize(1000);
}

void PacketReader::addByte(char byte) {
	if(buffer.size() <= index)
		buffer.resize(index+1000);
	buffer[index] = byte;
	index++;
	packetReady = false;
	if(
		(index == 0 && byte != 'D') || 
		(index == 1 && byte != 'A') ||
		(index == 2 && byte != 'T') ||
		(index == 3 && byte != 'A') 
	) {
		reset();
	}
	
	if(index == sizeof(Packetizer::Header) && !isHeaderOkay()) {
		reset();
	}
	
	if(index > sizeof(Packetizer::Header)) {
		if(!isPacketOkay())
			reset();
		else {
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

bool PacketReader::isPacketOkay() {
	Packetizer::Header* header = getPacketHeader();
	if(index != sizeof(Packetizer::Header) + header->length)
		return false;
	uint16_t sum = calcCheckSum(sizeof(Packetizer::Header), sizeof(Packetizer::Header) + header->length);
	if(sum != 0)
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
}
