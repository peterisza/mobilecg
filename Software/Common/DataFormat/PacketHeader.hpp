#ifndef _PACKET_HEADER_HPP
#define _PACKET_HEADER_HPP

#include <stdint.h>

namespace ecg {
	
struct PacketHeader {
	enum PacketType {
		STREAM_PACKET = 0
	};	
	PacketType packetType;
	uint16_t checksum;
};

}

#endif
