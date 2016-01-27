#include "EcgProcessor.h"
#include "EcgHeaderCommon.h"
#include "BitFifo.hpp"
#include "FlatEcgPredictor.hpp"
#include "DifferenceEcgCompressor.hpp"
#include <GLES2/gl2.h>
#include "EcgArea.h"

#include "log.h"

const int DECOMPRESS_BUFFER_STRIDE = ECG_MAX_SEND_SIZE/3+1;
static GLfloat decompressBuffer[ecg::DifferenceEcgCompressor::maxChannels][DECOMPRESS_BUFFER_STRIDE];

EcgProcessor::EcgProcessor(){
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

    //LOGD("numbits = %d, sampleCount = %d", header->numBits, header->sampleCount);

    ecg::DifferenceEcgCompressor decompressor(bitFifo, predictor);
    decompressor.setNumChannels(header->channelCount);

    if(header->channelCount > MAX_NUM_CHANNELS)
        LOGE("EcgProcessor max channel number exceeded.");

    int timesample [ecg::DifferenceEcgCompressor::maxChannels];
    for (int a=0; a<header->sampleCount; a++){
        decompressor.getSample(timesample);
        /*if(a < 10)
            LOGD("sample[%d][1]=%d", a, timesample[1]);*/
        /*if(a == 0)
            LOGD("%08X %08X %08X %08X %08X %08X %08X %08X", timesample[0], timesample[1], timesample[2], timesample[3], timesample[4], timesample[5], timesample[6], timesample[7]);
        */

        for (int c=0; c<header->channelCount; c++){
            decompressBuffer[c][a] = timesample[c]/200.0;
            if(c <= MAX_NUM_CHANNELS)
                decompressBuffer[c][a] = notchFilter[c].filter(decompressBuffer[c][a]);
        }
    }

    //LOGD("Pinapuci");

    EcgArea::instance().putData((GLfloat*)decompressBuffer, header->channelCount, header->sampleCount, DECOMPRESS_BUFFER_STRIDE);

}
