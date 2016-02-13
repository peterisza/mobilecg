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
 
#include "QRSDetector.hpp"
#include <stdlib.h>

static float numQRS[]={0.35473657163404165,0,-0.35473657163404165};
static float denQRS[]={0.6270403082828387,0.29052685673191625};

#define AVERAGE_START 3000
#define AVERAGE_RR_START 30
#define MIN_RR 16

#define FIXPOINT_DIV 0x1000

#define FP(x) ((int32_t)((x)*FIXPOINT_DIV))
#define FLOATMUL(intnum, y) (((intnum) * FP(y)) / FIXPOINT_DIV)

#define DEAD_TIME_PERCENT 0.3
#define CMP_THRESHOLD 0.5
#define MIN_THRESHOLD 1200

#define AMPLITUDE_AVERAGE_FACTOR 0.6
#define RR_AVERAGE_FACTOR 0.7

QRSDetector::QRSDetector(): filter(numQRS, denQRS) {

}

void QRSDetector::movingAverage(int32_t data, int32_t fixpointScale, int32_t &average){
	average = (average * fixpointScale + (FIXPOINT_DIV - fixpointScale) * data) / FIXPOINT_DIV;
}

void QRSDetector::qrsDetected(int32_t rrDistance, int32_t amplitude){
	if (qrsSinceReset==0){
		averageLevel = amplitude;
	} else if (qrsSinceReset==1){
		averageRR = rrDistance;
	} else {
		movingAverage(rrDistance, FP(RR_AVERAGE_FACTOR), averageRR);
		if (averageRR < MIN_RR)
			averageRR = MIN_RR;
	}

	if (qrsSinceReset>0){
		movingAverage(amplitude, FP(AMPLITUDE_AVERAGE_FACTOR), averageLevel);
	}

	qrsSinceReset++;
}

bool QRSDetector::process(int32_t data){
	data=abs(filter.filter(data));


	bool result = false;
	bool maxDetected = false;

	const int32_t deadtimeSamples = FLOATMUL(averageRR, DEAD_TIME_PERCENT);

	if (deadtimeRemaining){
		if (data > maxData){
			//If max detected during deadtime, reset deadtime counter
			//and save the position of the maximum.

			maxDetected = true;
		} else {
			deadtimeRemaining --;
			if (deadtimeRemaining == 0){
				//If it is end of deadtime, a QRS is detected somewhere 
				//during this time.

				int32_t RR = maxTimestamp - lastQRSTimestamp;
				lastQRSTimestamp = maxTimestamp;

				qrsDetected(RR, maxData);

				result = true;
			}
		}

		lastThreshold = data;
	} else {
		//Decrease the theshold until next QRS
		int32_t lastQRSDistance = timestamp - lastQRSTimestamp;
		int32_t qrsThreshold = averageLevel - (lastQRSDistance - deadtimeSamples)*FLOATMUL(averageLevel, 1.0-CMP_THRESHOLD) / (averageRR-deadtimeSamples);
		if (qrsThreshold < MIN_THRESHOLD)
			qrsThreshold = MIN_THRESHOLD;

		if (data > qrsThreshold){
			maxDetected = true;
		}

		lastThreshold = qrsThreshold;
	}

	if (maxDetected){
		maxData = data;
		maxTimestamp = timestamp;

		deadtimeRemaining = deadtimeSamples;
	}

	timestamp++;

	return result;
}

void QRSDetector::reset(){
	averageLevel = AVERAGE_START;
	averageRR = AVERAGE_RR_START;

	timestamp = 0;
	deadtimeRemaining = 0;
	qrsSinceReset = 0;
	lastQRSTimestamp = 0;
	lastThreshold = 0;
}

int32_t QRSDetector::getPulseRate(){
	if (qrsSinceReset < 2){
		return 0;
	} else 
		return (50*60)/averageRR;
}

int32_t QRSDetector::getLastThreshold(){
	return lastThreshold;
}
