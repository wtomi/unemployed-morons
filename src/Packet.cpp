//
// Created by tommy on 11.06.17.
//

#include "Packet.h"

Packet::Packet(const std::stringstream &stringstreamMessage, int rank, int tag) {
    this->rank = rank;
    this->tag = tag;
    this->stringstreamMessage = std::stringstream(stringstreamMessage.str());
}

Packet::SharedPtr Packet::Create(const std::stringstream &stringstreamMessage, int rank, int tag) {
    return Packet::SharedPtr(new Packet(stringstreamMessage, rank, tag));
}
