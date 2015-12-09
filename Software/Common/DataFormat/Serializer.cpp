#include "Serializer.hpp"
#include "PacketHeader.hpp"
#include "helpers.hpp"

using namespace ecg;

Serializer::Serializer(FifoBuffer **streams, int numStreams):
	streams(streams),
	numStreams(numStreams)
{
	
}

bool Serializer::makePacket(char* buffer, int totalSize) {
	int totalAvailable = 0;
	int toStoreTotal = 0;
	int headerSize = sizeof(PacketHeader);
	int dataSize = totalSize - 2*numStreams - headerSize;
	
	PacketHeader* header = (PacketHeader*) buffer;
	BigEndianInt16* sizes = (BigEndianInt16*) (buffer + headerSize);
	char* data = buffer + headerSize + 2*numStreams;
	
	for(int i = 0; i < numStreams; ++i)
		totalAvailable += streams[i].getAvailableBytes();

	for(int i = 0; i < numStreams; ++i) {
		int toStore = dataSize * streams[i]->getAvailableBytes() / totalAvailable;
		sizes[i] = toStore;
		toStoreTotal += toStore;
	}
	
	if(toStoreTotal > totalAvailable)
		return false;
	
	int correction = dataSize - toStoreTotal;
	
	for(int i = 0; i < numStreams; ++i) {
		if(correction < 0 && sizes[i] > 0) {
			sizes[i] = sizes[i] - 1;
			correction++;
		}
		if(correction > 0 && sizes[i] < streams[i]->getAvailableBytes()) {
			sizes[i] = sizes[i] + 1;
			correction--;
		}
		streams[i].popBytes(data, sizes[i]);
		data += sizes[i];
	}
	
	header->packetType = PacketHeader::DATA_PACKET;
	
	return true;
}

bool Serializer::readPacket(const char* buffer, int totalSize) {
	int totalAvailable = 0;
	int headerSize = sizeof(PacketHeader);
	int dataSize = totalSize - 2*numStreams - headerSize;
	
	PacketHeader* header = (PacketHeader*) buffer;
	BigEndianInt16* sizes = (BigEndianInt16*) (buffer + headerSize);
	const char* data = buffer + headerSize + 2*numStreams;
	
	if(header->packetType != PacketHeader::DATA_PACKET)
		return false;
	
	for(int i = 0; i < numStreams; ++i) {
		streams[i].pushBytes(data, sizes[i]);
		data += sizes[i];
	}
	
	return true;	
}
