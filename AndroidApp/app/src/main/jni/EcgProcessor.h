#ifndef ANDROIDAPP_ECGPROCESSOR_H
#define ANDROIDAPP_ECGPROCESSOR_H

#include "SignalConditioning/EcgFilters.hpp"

class EcgProcessor {
    private:
        EcgProcessor();
        static const int MAX_NUM_CHANNELS = 8;
        EcgFilter ecgFilter[MAX_NUM_CHANNELS];

        int pga;
        float currScale;
        float samplingFrequency;
    public:
        float getSamplingFrequency();
        static EcgProcessor &instance();

        void receivePacket(char *data, int len);
};


#endif //ANDROIDAPP_ECGPROCESSOR_H
