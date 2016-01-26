#include "Packetizer.h"

uint32_t Packetizer::packetId=0;

Packetizer::Packetizer() {
	resetChecksum();
}

Packetizer::~Packetizer() {
}

void Packetizer::startPacket(uint8_t *destBuffer, PacketType type, uint16_t length){
	Header *header = (Header *)destBuffer;
	header->signature = SIGNATURE;
	header->packetId = packetId;
	header->length = length;
	header->type = type;
	header->version = VERSION;
	header->reserved=0;

	resetChecksum();

	header->headerChecksum = 0;
    for (uint8_t *h = (uint8_t *)header; h<(uint8_t*)&header->headerChecksum; ++h ){
        header->headerChecksum += *h;
    }

    header->headerChecksum=-header->headerChecksum;
	packetId++;
}

void Packetizer::checksumBlock(uint8_t *data, int cnt){
	for (; cnt; cnt--, data++){
		checksum += (Checksum)(*data);
	}
}

Packetizer::Checksum Packetizer::getChecksum(){
	return -checksum;
}

void Packetizer::resetChecksum(){
	checksum = 0;
}
