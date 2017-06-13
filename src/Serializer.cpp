//
// Created by tommy on 11.06.17.
//

#include "Serializer.h"

std::shared_ptr<std::stringstream> Serializer::serialize(Message::SharedPtr message) {
    auto stringstreamMsg = std::make_shared<std::stringstream>();
    cereal::BinaryOutputArchive outputArchive(*(stringstreamMsg.get()));
    outputArchive(message);
    return stringstreamMsg;
}

Message::SharedPtr Serializer::deserialize(std::shared_ptr<std::stringstream> stringstreamMsg) {
    auto message = Message::Create(0, 0, 0);
    cereal::BinaryInputArchive inputArchive(*(stringstreamMsg.get()));
    inputArchive(message);
    return message;
}
