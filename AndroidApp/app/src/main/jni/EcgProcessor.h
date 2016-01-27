#ifndef ANDROIDAPP_ECGPROCESSOR_H
#define ANDROIDAPP_ECGPROCESSOR_H

#include "488Hz50HzNotchFilter.hpp"

class EcgProcessor {
    private:
        EcgProcessor();
        static const int MAX_NUM_CHANNELS = 8;
        NotchFilter notchFilter[MAX_NUM_CHANNELS];
    public:
        static EcgProcessor &instance();

        void receivePacket(char *data, int len);
};


#endif //ANDROIDAPP_ECGPROCESSOR_H
