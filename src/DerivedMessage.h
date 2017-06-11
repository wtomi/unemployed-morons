//
// Created by tommy on 11.06.17.
//

#ifndef UNEMPLOYED_MORRONS_DERIVEDMESSAGE_H
#define UNEMPLOYED_MORRONS_DERIVEDMESSAGE_H


#include "Message.h"
#include <cereal/types/base_class.hpp>

class DerivedMessage : public Message {
public:
    typedef std::shared_ptr<DerivedMessage> SharedPtr;

    std::string myword;

    static DerivedMessage::SharedPtr Create();
    void sayWord();

private:
    friend class cereal::access;
    DerivedMessage(): Message() {}

    template<class Archive>
    void serialize(Archive &archive) {
        archive(cereal::base_class<Message>(this), myword);
    }
};

CEREAL_REGISTER_TYPE(DerivedMessage);

#endif //UNEMPLOYED_MORRONS_DERIVEDMESSAGE_H
