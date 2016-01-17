#include "FlatEcgPredictor.hpp"

using namespace ecg;

FlatEcgPredictor::FlatEcgPredictor(int pNumChannels):
	numChannels(pNumChannels)
{
	reset();
}

void FlatEcgPredictor::putSample(const int* channels) {
	for(int i = 0; i < numChannels; ++i)
		prediction[i] = channels[i];	
}

int FlatEcgPredictor::getPrediction(int channel) {
	return prediction[channel];
}

void FlatEcgPredictor::reset() {
	for(int i = 0; i < numChannels; ++i)
		prediction[i] = 0;	
}
