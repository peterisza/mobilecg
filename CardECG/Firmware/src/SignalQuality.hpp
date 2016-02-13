#ifndef _SIGNALQUALITY_H_
#define _SIGNALQUALITY_H_

#include <stdint.h>

class SignalQuality{
	public:
		SignalQuality();
		void processSample(int32_t raw, int8_t filtered);
		bool isSignalGood();
		int signalHasBeenGoodFor();
		int getNoiseQuantity();
		void reset();
	private:
		int32_t prevSample, prev2Sample;
		bool lastSampleGood;
		int howLong;
		int noiseQuantity;
		int oobCounter;
};

#endif
