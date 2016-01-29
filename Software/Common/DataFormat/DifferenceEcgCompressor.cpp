#include "DifferenceEcgCompressor.hpp"

#include <stdio.h>
using namespace ecg;


DifferenceEcgCompressor::DifferenceEcgCompressor(BitFifo &pBitStream, IEcgPredictor& pEcgPredictor):
	bitStream(pBitStream),
	ecgPredictor(pEcgPredictor)
{
	numChannels=0;
}

bool DifferenceEcgCompressor::putSample(const int32_t* channels) {
	for(unsigned int i = 0; i < numChannels; ++i) {
		int32_t diff = channels[i] - ecgPredictor.getPrediction(i);
		//printf(" newdata=%d pred=%d\n", channels[i], ecgPredictor.getPrediction(i));
		bool okay = true;
		if(diff >= smallMin && diff <= smallMax) {
			okay &= bitStream.pushBits(0, 1);
			okay &= bitStream.pushBits(diff, smallBitNum);
			//printf("S %d\n", diff);
		} else {
			okay &= bitStream.pushBits(1, 1);
			okay &= bitStream.pushBits(channels[i], fullBitNum);
			//printf("F %d\n", diff);
		}
		if(!okay)
			return false;
	}
	ecgPredictor.putSample(channels);
	return true;
}

bool DifferenceEcgCompressor::getSample(int32_t *channels) {
	for(unsigned int i = 0; i < numChannels; ++i) {
		int full = bitStream.popBits(1);
		//printf('');
		int bitNum = full ? fullBitNum : smallBitNum;
		if(bitStream.getAvailableBits() < bitNum)
			return false;
		if(full)
			channels[i] = bitStream.popBitsSigned(fullBitNum);
		else
			channels[i] = ecgPredictor.getPrediction(i) + bitStream.popBitsSigned(smallBitNum);
	}	
	ecgPredictor.putSample(channels);
	return true;
}

void DifferenceEcgCompressor::setNumChannels(unsigned pNumChannels){
	numChannels=pNumChannels;
	if(numChannels > maxChannels)
		numChannels = maxChannels;
}
