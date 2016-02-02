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
	int32_t sampleOfChannels[ecg::DifferenceEcgCompressor::maxChannels];

	ecg::BitFifo compressFifo;
	ecg::FlatEcgPredictor ecgPredictor;
	ecg::DifferenceEcgCompressor compressor;

	Packetizer *packetizer;
	bool testSignal;

	static const float ECG_LSB_IN_MV;
	static const int ECG_CHOP_BITS;
	float currLsbInMv;
	float currFrequency;


	TestSignalGenerator testGenerator;
};

#endif /* SRC_ECGSENDER_H_ */
