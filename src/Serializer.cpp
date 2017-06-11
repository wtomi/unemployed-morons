//
// Created by tommy on 11.06.17.
//

#include "Serializer.h"

std::stringstream Serializer::serialize(Message::SharedPtr message) {
    std::stringstream stringstreamMsg;
    cereal::BinaryOutputArchive outputArchive(stringstreamMsg);
    outputArchive(message);
    return stringstreamMsg;
}

Message::SharedPtr Serializer::deserialize(std::stringstream &stringstreamMsg) {
    auto message = Message::Create();
    cereal::BinaryInputArchive inputArchive(stringstreamMsg);
    inputArchive(message);
    return message;
}
