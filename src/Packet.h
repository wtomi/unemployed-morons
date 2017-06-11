//
// Created by tommy on 11.06.17.
//

#ifndef UNEMPLOYED_MORRONS_PACKAGE_H
#define UNEMPLOYED_MORRONS_PACKAGE_H


#include <sstream>

class Packet {
public:
    int rank;
    int tag;
    std::stringstream stringstreamMessage;

    Packet(const std::stringstream &stringstreamMessage, int rank, int tag) {
        this->rank = rank;
        this->tag = tag;
        this->stringstreamMessage = std::stringstream(stringstreamMessage.str());
    }

    Packet(const Packet &aPackage) {
        Packet(aPackage.stringstreamMessage, aPackage.rank, aPackage.tag);
    }
};


#endif //UNEMPLOYED_MORRONS_PACKAGE_H
