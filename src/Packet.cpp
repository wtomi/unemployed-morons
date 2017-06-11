//
// Created by tommy on 11.06.17.
//

#include "Packet.h"

Packet::Packet(std::shared_ptr<std::stringstream> stringstreamMessage, int rank, int tag) {
    this->rank = rank;
    this->tag = tag;
    this->stringstreamMessage = stringstreamMessage;
}

Packet::SharedPtr Packet::Create(std::shared_ptr<std::stringstream> stringstreamMessage, int rank, int tag) {
    return Packet::SharedPtr(new Packet(stringstreamMessage, rank, tag));
}
