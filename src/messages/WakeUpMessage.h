//
// Created by tommy on 18.06.17.
//

#ifndef UNEMPLOYED_MORRONS_WAKEUPMESSAGE_H
#define UNEMPLOYED_MORRONS_WAKEUPMESSAGE_H


#include "Message.h"

class WakeUpMessage : public Message {
public:
    typedef std::shared_ptr<WakeUpMessage> SharedPtr;

    static SharedPtr Create(int rank, int tag);

private:
    friend class cereal::access;
    WakeUpMessage() : Message() {}
    WakeUpMessage(int rank, int tag);

    template<class Archive>
    void serialize(Archive &ar) {
        ar(cereal::base_class<Message>(this));
    }
};

CEREAL_REGISTER_TYPE(WakeUpMessage);


#endif //UNEMPLOYED_MORRONS_WAKEUPMESSAGE_H
