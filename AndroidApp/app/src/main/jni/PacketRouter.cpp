#include "PacketRouter.h"
#include "EcgProcessor.h"

#include "log.h"
PacketRouter::PacketRouter(){

}

PacketRouter &PacketRouter::instance(){
    static PacketRouter r;
    return r;
}

void PacketRouter::packetReceived(Packetizer::Header *header, char *data){

    LOGD("CSOMCSIIIIII");
    switch (header->type){
        case Packetizer::ECG:
            EcgProcessor::instance().receivePacket(data, (int)header->length);
            break;
        default:
            break;
    }
}