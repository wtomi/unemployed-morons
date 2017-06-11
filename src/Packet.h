//
// Created by tommy on 11.06.17.
//

#ifndef UNEMPLOYED_MORRONS_PACKAGE_H
#define UNEMPLOYED_MORRONS_PACKAGE_H


#include <sstream>
#include <memory>

class Packet {
public:
    typedef std::shared_ptr<Packet> SharedPtr;

    int rank;
    int tag;
    std::shared_ptr<std::stringstream> stringstreamMessage;

    static Packet::SharedPtr Create(std::shared_ptr<std::stringstream> stringstreamMessage, int rank, int tag);

private:
    Packet(std::shared_ptr<std::stringstream> stringstreamMessage, int rank, int tag);
};


#endif //UNEMPLOYED_MORRONS_PACKAGE_H
