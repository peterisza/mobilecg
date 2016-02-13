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
 
#ifndef SRC_PACKETIZER_H_
#define SRC_PACKETIZER_H_

#include <stdint.h>

class Packetizer {
public:
	struct Header{
		uint32_t signature;
		uint16_t length;
		uint8_t version;
		uint8_t type;
		uint32_t packetId;
		uint8_t reserved;
		uint8_t headerChecksum;
	} __attribute__((packed));

	enum PacketType {ECG=0};

	static const uint32_t HEADER_SIZE = sizeof(Header);
	static const uint32_t SIGNATURE = 0x41544144;
	static const uint8_t VERSION = 0;
	typedef uint16_t Checksum;

	Packetizer();
	virtual ~Packetizer();

	void startPacket(uint8_t *destBuffer, PacketType type, uint16_t length);
	void checksumBlock(uint8_t *data, int cnt);
	Checksum getChecksum();
private:


	static uint32_t packetId;
	Checksum checksum;
	void resetChecksum();
};

#endif /* SRC_PACKETIZER_H_ */
