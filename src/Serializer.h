//
// Created by tommy on 11.06.17.
//

#ifndef UNEMPLOYED_MORRONS_SERIALIZER_H
#define UNEMPLOYED_MORRONS_SERIALIZER_H


#include <sstream>
#include "Message.h"

class Serializer {
public:
    static std::stringstream serialize(Message::SharedPtr message);
    static Message::SharedPtr deserialize(std::stringstream &stringstreamMsg);
};


#endif //UNEMPLOYED_MORRONS_SERIALIZER_H
