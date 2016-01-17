#include "DifferenceEcgCompressor.hpp"

#include <stdio.h>
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
		//printf(" newdata=%d pred=%d\n", channels[i], ecgPredictor.getPrediction(i));
		if(diff >= smallMin && diff <= smallMax) {
			bitStream.pushBits(0, 1);
			bitStream.pushBits(diff, smallBitNum);
			//printf("S %d\n", diff);
		} else {
			bitStream.pushBits(1, 1);
			bitStream.pushBits(channels[i], fullBitNum);
			//printf("F %d\n", diff);
		}
	}
	ecgPredictor.putSample(channels);
}

bool DifferenceEcgCompressor::getSample(int *channels) {
	for(int i = 0; i < numChannels; ++i) {
		int full = bitStream.popBits(1);
		//printf('');
		if(full)
			channels[i] = bitStream.popBitsSigned(fullBitNum);
		else
			channels[i] = ecgPredictor.getPrediction(i) + bitStream.popBitsSigned(smallBitNum);
	}	
	ecgPredictor.putSample(channels);
}
