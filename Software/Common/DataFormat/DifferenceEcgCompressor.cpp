#include "DifferenceEcgCompressor.hpp"

using namespace ecg;

DifferenceEcgCompressor::DifferenceEcgCompressor(BitFifo &bitStream, unsigned numChannels, IEcgPredictor& ecgPredictor):
	bitStream(bitStream),
	numChannels(numChannels),
	ecgPredictor(ecgPredictor)
{
	if(numChannels > maxChannels)
		numChannels = maxChannels;
}

bool DifferenceEcgCompressor::putSample(const int* channels) {
	for(int i = 0; i < numChannels; ++i) {
		int diff = channels[i] - ecgPredictor.getPrediction(i);
		bitStream.pushBits(diff, fullBitNum);
	}
	ecgPredictor.putSample(channels);
}

bool DifferenceEcgCompressor::getSample(int *channels) {
	for(int i = 0; i < numChannels; ++i) {
		int diff = bitStream.popBits(fullBitNum);
		channels[i] = ecgPredictor.getPrediction(i) + diff;
	}	
	ecgPredictor.putSample(channels);
}
