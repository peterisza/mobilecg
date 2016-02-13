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