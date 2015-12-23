#ifndef _STREAM_SERIALIZER_HPP
#define _STREAM_SERIALIZER_HPP

#include <stdint.h>
#include "BitFifo.hpp"

/* Serializes many binary streams into endian-safe packets of arbitrary length. */

namespace ecg {

class StreamSerializer {
	public:
		StreamSerializer(BitFifo** streams, int numStreams);
		bool makePacket(char* buffer, int totalSize);
		bool readPacket(const char* buffer, int totalSize);
		
	private:
		BitFifo** streams;
		int numStreams;
};

}

#endif
