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
static GLfloat decompressBuffer[ecg::DifferenceEcgCompressor::maxChannels][DECOMPRESS_BUFFER_STRIDE];

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
                //filteredSampleNum[c]++;
            }
        }
    }

    EcgArea::instance().putData((GLfloat*)decompressBuffer, header->channelCount, filteredSampleNum[0], DECOMPRESS_BUFFER_STRIDE);

}

float EcgProcessor::getSamplingFrequency(){
    return samplingFrequency;
}
