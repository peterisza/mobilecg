#include "EcgProcessor.h"
#include "EcgHeaderCommon.h"
#include "BitFifo.hpp"
#include "FlatEcgPredictor.hpp"
#include "DifferenceEcgCompressor.hpp"
#include <GLES2/gl2.h>
#include "EcgArea.h"

#include "log.h"

static GLfloat decompressBuffer[ecg::DifferenceEcgCompressor::maxChannels][ECG_MAX_SEND_SIZE/3+1];

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

    /*LOGD("csomag eleje: %02X %02X %02X %02X",
         data[sizeof(ECGHeader)],
         data[sizeof(ECGHeader)+1],
         data[sizeof(ECGHeader)+2],
         data[sizeof(ECGHeader)+3]);*/

    int timesample [ecg::DifferenceEcgCompressor::maxChannels];
    for (int a=0; a<header->sampleCount; a++){
        decompressor.getSample(timesample);
        //LOGD("sample %d", timesample[0]);
        for (int c=0; c<header->channelCount; c++){
            decompressBuffer[c][a] = timesample[c]/10.0;
            if (a>0){
                decompressBuffer[c][a]-=decompressBuffer[c][a-1];
            }
        }
    }

    //LOGD("Pinapuci");

    EcgArea::instance().putData((GLfloat*)decompressBuffer,  header->channelCount, header->sampleCount );

}
