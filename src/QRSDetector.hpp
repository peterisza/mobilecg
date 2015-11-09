#ifndef _QRSDETECTOR_H_
#define _QRSDETECTOR_H_

#include <stdint.h>
#include "IIRFilter.hpp"

class QRSDetector{
	public:
		QRSDetector();
		bool process(int32_t data);
		void reset();

		int32_t getPulseRate();
		int32_t getLastThreshold();
	private:
		IIRFilter <0x1000000, 3, 2> filter;
		int32_t averageLevel;
		int32_t averageRR;

		int32_t maxData;
		int32_t maxTimestamp;

		int32_t deadtimeRemaining;
		int32_t timestamp;

		int32_t lastQRSTimestamp;

		int32_t qrsSinceReset;

		int32_t lastThreshold;

		void qrsDetected(int32_t rrDistance, int32_t amplitude);

		static void movingAverage(int32_t data, int32_t fixpointScale, int32_t &average);
};

#endif
