#ifndef SRC_ECGSENDER_H_
#define SRC_ECGSENDER_H_

#include <stdint.h>

#include "Packetizer.h"

class ECGSender {
public:
	ECGSender(Packetizer &packetizer);
	virtual ~ECGSender();

	void send();
private:
	struct ECGHeader{
		uint8_t channelCount;
		uint32_t sampleCount;
	} __attribute__((packed));

	Packetizer *packetizer;
};

#endif /* SRC_ECGSENDER_H_ */
