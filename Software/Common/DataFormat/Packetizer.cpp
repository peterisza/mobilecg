/*
 * This file is part of MobilECG, an open source clinical grade Holter
 * ECG. For more information visit http://mobilecg.hu
 *
 * Copyright (C) 2016  Robert Csordas, Peter Isza
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
