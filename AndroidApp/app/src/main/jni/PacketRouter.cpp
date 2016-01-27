#include "PacketRouter.h"
#include "EcgProcessor.h"

#include "log.h"
PacketRouter::PacketRouter(){
    prevIndex=-1;
}

PacketRouter &PacketRouter::instance(){
    static PacketRouter r;
    return r;
}

void PacketRouter::packetReceived(Packetizer::Header *header, char *data){
    if (prevIndex>=0){
        int next=prevIndex+1;
        if (header->packetId!=next){
            LOGE("Packet missing: %d",next);
        }
    }
    prevIndex=header->packetId;

    switch (header->type){
        case Packetizer::ECG:
            EcgProcessor::instance().receivePacket(data, (int)header->length);
            break;
        default:
            break;
    }
}