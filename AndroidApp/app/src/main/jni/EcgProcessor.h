#ifndef ANDROIDAPP_ECGPROCESSOR_H
#define ANDROIDAPP_ECGPROCESSOR_H

class EcgProcessor {
    private:
        EcgProcessor();
    public:
        static EcgProcessor &instance();

        void receivePacket(char *data, int len);

};


#endif //ANDROIDAPP_ECGPROCESSOR_H
