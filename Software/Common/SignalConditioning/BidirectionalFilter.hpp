#ifndef _TWO_WAY_FILTER_H
#define _TWO_WAY_FILTER_H

#include "IFilter.hpp"
#include "CircularBuffer.h"

template <int responseDecayTime, int blockSize>
class BidirectionalFilter {
public:
	BidirectionalFilter(IFilter *forward, IFilter *backward):
		forward(forward),
		backward(backward)
	{
		forward->reset();
		inputBuffer.resize(responseDecayTime + blockSize);
		inputBuffer.assign(inputBuffer.size(), 0);
		outputBuffer.resize(blockSize);
		inputIndex = 0;
		outputIndex = 0;
	}
	
	void putSample(FilterNumberType sample) {
		sample = forward->filter(sample);
		inputBuffer[inputIndex] = sample;
		inputIndex++;
		if(inputIndex == inputBuffer.size())
			inputIndex = 0;
	}
	
	bool isOutputAvailable() {
		
	}
	
	FilterNumberType getSample() {
		
	}
	
private:
	IFilter *forward, *backward;
	CircularBuffer<FilterNumberType, responseDecayTime + blockSize> inputBuffer;
	CircularBuffer<FilterNumberType, blockSize> outputBuffer;
};

#endif
