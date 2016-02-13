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
