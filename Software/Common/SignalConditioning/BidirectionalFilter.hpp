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
	}
	
	void putSample(FilterNumberType sample) {
		sample = forward->filter(sample);
		inputBuffer.add(sample);
		if(inputBuffer.isFull()) {
			backward->reset();
			for(int i = inputBuffer.used()-1; i >= 0; --i) {
				FilterNumberType tmp = backward->filter(inputBuffer[i]);
				if(i < blockSize)
					inputBuffer[i] = tmp;
			}
			for(int i = 0; i < blockSize; ++i) {
				outputBuffer.add(inputBuffer.get());
			}
		}
	}
	
	bool isOutputAvailable() {
		return !outputBuffer.isEmpty();
	}
	
	FilterNumberType getSample() {
		if(!isOutputAvailable())
			return 0;
		return outputBuffer.get();
	}
	
private:
	IFilter *forward, *backward;
	CircularBuffer<FilterNumberType, responseDecayTime + blockSize> inputBuffer;
	CircularBuffer<FilterNumberType, blockSize> outputBuffer;
};

#endif
