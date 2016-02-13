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
 
#ifndef _PACKET_READER_HPP
#define _PACKET_READER_HPP

#include "Packetizer.h"
#include <string>

class PacketReader {
public:
	PacketReader();
	void addByte(char byte);
	bool isPacketReady();
	void reset();
	
	/* only valid until the next byte is added */
	Packetizer::Header* getPacketHeader();
	
	/* only valid until the next byte is added */	
	char* getPacketData();
private:
	static const int MAX_BUFFER_SIZE = 8192;

	bool isHeaderOkay();
	bool isPacketOkay();
	bool isSignatureOkay();
	bool packetReceived();
	
	int calcCheckSum(int start, int end);
	void lookForMissedPackets(int length);
	
	std::string buffer;
	int index;
	bool packetReady;
};

#endif
