#ifndef SRC_ECGSENDER_H_
#define SRC_ECGSENDER_H_

#include <stdint.h>

#include "Packetizer.h"
#include <BitFifo.hpp>
#include <DifferenceEcgCompressor.hpp>
#include <FlatEcgPredictor.hpp>
#include <ADS1298.h>
#include "EcgHeaderCommon.h"
#include "TestSignalGenerator.h"

class ECGSender {
public:
	ECGSender(Packetizer &packetizer);
	virtual ~ECGSender();

	void send();
private:
	uint8_t compressBuffer[ECG_COMPRESS_OUTPUT_BUFFER_SIZE];
	int sampleOfChannels[ecg::DifferenceEcgCompressor::maxChannels];

	ecg::BitFifo compressFifo;
	ecg::FlatEcgPredictor ecgPredictor;
	ecg::DifferenceEcgCompressor compressor;

	ADS1298::ECGBlock tempBlock;


	Packetizer *packetizer;
	bool testSignal;


	TestSignalGenerator testGenerator;
};

#endif /* SRC_ECGSENDER_H_ */
