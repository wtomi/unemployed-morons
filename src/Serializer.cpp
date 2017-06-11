//
// Created by tommy on 11.06.17.
//

#include "Serializer.h"

std::stringstream Serializer::serialize(Message message) {
    std::stringstream stringstreamMsg;
    cereal::BinaryOutputArchive outputArchive(stringstreamMsg);
    outputArchive(message);
    return stringstreamMsg;
}

Message Serializer::deserialize(std::stringstream &stringstreamMsg) {
    Message message;
    cereal::BinaryInputArchive inputArchive(stringstreamMsg);
    inputArchive(message);
    return message;
}
