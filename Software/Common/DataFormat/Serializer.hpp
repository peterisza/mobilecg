#ifndef _SERIALIZER_HPP
#define _SERIALIZER_HPP

#include <stdint.h>
#include "FifoBuffer.hpp"

/* Serializes many binary streams into endian-safe packets of arbitrary length. */

namespace ecg {

class Serializer {
	public:
		Serializer(FifoBuffer** streams, int numStreams);
		bool makePacket(char* buffer, int totalSize);
		bool readPacket(const char* buffer, int totalSize);
		
	private:
		FifoBuffer* streams;
		int numStreams;
};

}

#endif
