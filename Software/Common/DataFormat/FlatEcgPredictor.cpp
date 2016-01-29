#include "FlatEcgPredictor.hpp"

using namespace ecg;

FlatEcgPredictor::FlatEcgPredictor()
{
	numChannels=0;
	reset();
}

void FlatEcgPredictor::putSample(const int32_t* channels) {
	for(int i = 0; i < numChannels; ++i)
		prediction[i] = channels[i];
}

int32_t FlatEcgPredictor::getPrediction(int channel) {
	return prediction[channel];
}

void FlatEcgPredictor::reset() {
	for(int i = 0; i < numChannels; ++i)
		prediction[i] = 0;	
}

void FlatEcgPredictor::setNumChannels(const int pNumChannels){
	numChannels = pNumChannels;
}
