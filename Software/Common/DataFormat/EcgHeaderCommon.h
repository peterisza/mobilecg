/*
 * EcgHeaderCommon.h
 *
 *  Created on: 2016. jan. 24.
 *      Author: xdever
 */

#ifndef SRC_ECGHEADERCOMMON_H_
#define SRC_ECGHEADERCOMMON_H_

#include <stdint.h>

struct ECGHeader{
	uint8_t channelCount;
	uint32_t sampleCount;
	uint32_t numBits;
	float lsbInMv;
	float samplingFrequency;
} __attribute__((packed));

static const int ECG_MAX_SEND_SIZE = 2160;
//The worst case output size after compression. It is very unlikely that
//this will be ever filled, but it's the theoretical maximum.
static const int ECG_COMPRESS_OUTPUT_BUFFER_SIZE = 25*ECG_MAX_SEND_SIZE/24+1;


#endif /* SRC_ECGHEADERCOMMON_H_ */
