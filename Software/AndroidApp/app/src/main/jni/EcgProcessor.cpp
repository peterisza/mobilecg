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
 
#include "EcgProcessor.h"
#include "DataFormat/EcgHeaderCommon.h"
#include "DataFormat/BitFifo.hpp"
#include "DataFormat/FlatEcgPredictor.hpp"
#include "DataFormat/DifferenceEcgCompressor.hpp"
#include <GLES2/gl2.h>
#include "EcgArea.h"

#include "log.h"

//#define DEBUG

const int DECOMPRESS_BUFFER_STRIDE = ECG_MAX_SEND_SIZE/3+1;
static GLfloat decompressBuffer[12][DECOMPRESS_BUFFER_STRIDE];

EcgProcessor::EcgProcessor(){
    samplingFrequency=500.0;
}

EcgProcessor &EcgProcessor::instance(){
    static EcgProcessor ecg;
    return ecg;
}

void EcgProcessor::receivePacket(char *data, int len){
    if (len<sizeof(ECGHeader))
        return;

    ECGHeader *header = (ECGHeader *)data;
    ecg::BitFifo bitFifo(data+sizeof(ECGHeader),(header->numBits+7)/8, header->numBits);
    ecg::FlatEcgPredictor predictor;
    predictor.setNumChannels(header->channelCount);
    predictor.reset();

    #ifdef DEBUG
        LOGD("numbits = %d, sampleCount = %d", header->numBits, header->sampleCount);
    #endif

    ecg::DifferenceEcgCompressor decompressor(bitFifo, predictor);
    decompressor.setNumChannels(header->channelCount);

    samplingFrequency=header->samplingFrequency;

    if(header->channelCount > MAX_NUM_CHANNELS) {
        LOGE("EcgProcessor max channel number exceeded.");
        return;
    }

    int32_t timesample [ecg::DifferenceEcgCompressor::maxChannels];

    int filteredSampleNum[MAX_NUM_CHANNELS];
    for (int c=0; c<header->channelCount; c++) {
        filteredSampleNum[c] = 0;
    }

    for (int a=0; a<header->sampleCount; a++){
        decompressor.getSample(timesample);

        #ifdef DEBUG
        if(a == 0)
            LOGD("%08X %08X %08X %08X %08X %08X %08X %08X", timesample[0], timesample[1], timesample[2], timesample[3], timesample[4], timesample[5], timesample[6], timesample[7]);
        #endif

        for (int c=0; c<header->channelCount; c++){
            decompressBuffer[c][a] = timesample[c] * header->lsbInMv;
            if(c <= MAX_NUM_CHANNELS) {
                ecgFilter[c].putSample(decompressBuffer[c][a]);
                if(ecgFilter[c].isOutputAvailable()) {
                    int index = filteredSampleNum[c];
                    filteredSampleNum[c]++;
                    decompressBuffer[c][a] = ecgFilter[c].getSample();
                }
            }
        }
    }

    for(int a = 0; a < filteredSampleNum[0]; a++) {
        EcgProcessor::calculate12Channels(&decompressBuffer[0][a], &decompressBuffer[0][a], DECOMPRESS_BUFFER_STRIDE);
    }

    EcgArea::instance().putData((GLfloat*)decompressBuffer, header->channelCount, filteredSampleNum[0], DECOMPRESS_BUFFER_STRIDE);

}


float EcgProcessor::getSamplingFrequency(){
    return samplingFrequency;
}

void EcgProcessor::calculate12Channels(float *input, float *output, int stride) {
    float I = input[1*stride];
    float II = input[2*stride];
    float III = II - I;
    float V1 = input[7*stride];
    float V2 = input[3*stride];
    float V3 = input[4*stride];
    float V4 = input[5*stride];
    float V5 = input[6*stride];
    float V6 = input[0*stride];
    float aVR = (-II-I)/3;
    float aVL = (I-III)/3;
    float aVF = (II+III)/3;
    output[0*stride] = I;
    output[1*stride] = II;
    output[2*stride] = III;
    output[3*stride] = aVR;
    output[4*stride] = aVL;
    output[5*stride] = aVF;
    output[6*stride] = V1;
    output[7*stride] = V2;
    output[8*stride] = V3;
    output[9*stride] = V4;
    output[10*stride] = V5;
    output[11*stride] = V6;
}
