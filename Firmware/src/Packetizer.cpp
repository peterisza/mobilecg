#include "Packetizer.h"

Packetizer::Packetizer() {
	packetId=0;
	resetChecksum();
}

Packetizer::~Packetizer() {
}

void Packetizer::startPacket(uint8_t *destBuffer, uint16_t length){
	Header *header = (Header *)destBuffer;
	header->signature = SIGNATURE;
	header->packetId = packetId;
	header->length = length;

	packetId++;
}

void Packetizer::checksumBlock(uint8_t *data, int cnt){
	for (; cnt; cnt--, data++){
		checksum += (Checksum)(*data);
	}
}

Packetizer::Checksum Packetizer::getChecksum(){
	return checksum;
}

void Packetizer::resetChecksum(){
	checksum = 0;
}
