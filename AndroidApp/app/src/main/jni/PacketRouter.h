#ifndef ANDROIDAPP_PACKETROUTER_H
#define ANDROIDAPP_PACKETROUTER_H

#include "Packetizer.h"

class PacketRouter {
    private:
        PacketRouter();
        int prevIndex;
    public:
        static PacketRouter &instance();
        void packetReceived(Packetizer::Header *header, char *data);
};


#endif //ANDROIDAPP_PACKETROUTER_H
