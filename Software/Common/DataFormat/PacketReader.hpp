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
	const char* getPacketData();
private:
	static const int MAX_BUFFER_SIZE = 8192;

	void fixEndianness();
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
