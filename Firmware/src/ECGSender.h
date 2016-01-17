#ifndef SRC_ECGSENDER_H_
#define SRC_ECGSENDER_H_

#include <stdint.h>

#include "Packetizer.h"
#include <BitFifo.hpp>
#include <DifferenceEcgCompressor.hpp>
#include <FlatEcgPredictor.hpp>
#include <ADS1298.h>

class ECGSender {
public:
	ECGSender(Packetizer &packetizer);
	virtual ~ECGSender();

	void send();
private:
	static const int MAX_SEND_SIZE = 2160;
	//The worst case output size after compression. It is very unlikely that
	//this will be ever filled, but it's the theoretical maximum.
	static const int COMPRESS_OUTPUT_BUFFER = 25*MAX_SEND_SIZE/24+1;

	uint8_t compressBuffer[COMPRESS_OUTPUT_BUFFER];
	int sampleOfChannels[ecg::DifferenceEcgCompressor::maxChannels];

	ecg::BitFifo compressFifo;
	ecg::FlatEcgPredictor ecgPredictor;
	ecg::DifferenceEcgCompressor compressor;

	ADS1298::ECGBlock tempBlock;

	struct ECGHeader{
		uint8_t channelCount;
		uint32_t sampleCount;
		uint32_t numBits;
	} __attribute__((packed));

	Packetizer *packetizer;
};

#endif /* SRC_ECGSENDER_H_ */
