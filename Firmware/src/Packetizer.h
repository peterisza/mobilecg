#ifndef SRC_PACKETIZER_H_
#define SRC_PACKETIZER_H_

#include <stdint.h>

class Packetizer {
public:
	static const uint32_t HEADER_SIZE = 10;
	static const uint32_t SIGNATURE = 0x41544144;
	typedef uint16_t Checksum;

	Packetizer();
	virtual ~Packetizer();

	void startPacket(uint8_t *destBuffer, uint16_t length);
	void checksumBlock(uint8_t *data, int cnt);
	Checksum getChecksum();
private:
	struct Header{
		uint32_t signature;
		uint32_t packetId;
		uint16_t length;
	} __attribute__((packed));

	uint32_t packetId;
	Checksum checksum;
	void resetChecksum();
};

#endif /* SRC_PACKETIZER_H_ */
