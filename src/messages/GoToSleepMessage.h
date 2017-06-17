//
// Created by tommy on 18.06.17.
//

#ifndef UNEMPLOYED_MORRONS_GOTOSLEEP_H
#define UNEMPLOYED_MORRONS_GOTOSLEEP_H


#include "Message.h"

class GoToSleepMessage : public Message {
public:
    typedef std::shared_ptr<GoToSleepMessage> SharedPtr;

    static SharedPtr Create(int rank, int tag);

private:
    friend class cereal::access;
    GoToSleepMessage() : Message() {}
    GoToSleepMessage(int rank, int tag);

    template<class Archive>
    void serialize(Archive &ar) {
        ar(cereal::base_class<Message>(this));
    }
};

CEREAL_REGISTER_TYPE(GoToSleepMessage);

#endif //UNEMPLOYED_MORRONS_GOTOSLEEP_H
