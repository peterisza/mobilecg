#include "FlatEcgPredictor.hpp"

using namespace ecg;

FlatEcgPredictor::FlatEcgPredictor(int numChannels):
	numChannels(numChannels)
{
	reset();
}

void FlatEcgPredictor::putSample(const int* channels) {
	for(int i = 0; i < numChannels; ++i)
		prediction[i] = 0;	
}

int FlatEcgPredictor::getPrediction(int channel) {
	return prediction[channel];
}

void FlatEcgPredictor::reset() {
	for(int i = 0; i < numChannels; ++i)
		prediction[i] = 0;	
}
