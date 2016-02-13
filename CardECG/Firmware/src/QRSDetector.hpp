/*
 * This file is part of MobilECG, an open source clinical grade Holter
 * ECG. For more information visit http://mobilecg.hu
 *
 * Copyright (C) 2016  Robert Csordas, Peter Isza
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
 
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
