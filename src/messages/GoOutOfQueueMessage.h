//
// Created by tommy on 16.06.17.
//

#ifndef UNEMPLOYED_MORRONS_GOOUTOFQUEUEMESSAGE_H
#define UNEMPLOYED_MORRONS_GOOUTOFQUEUEMESSAGE_H


#include "Message.h"

class GoOutOfQueueMessage : public Message {
public:
    typedef std::shared_ptr<GoOutOfQueueMessage> SharedPtr;
    static SharedPtr Create(int rank, int tag, int companyId, long requestClock);

    int companyId;
    long requestClock;
private:
    friend class cereal::access;
    GoOutOfQueueMessage(): Message() {}
    GoOutOfQueueMessage(int rank, int tag, int companyId, long requestClock);

    template<class Archive>
    void serialize(Archive &ar) {
        ar(cereal::base_class<Message>(this), companyId, requestClock);
    }
};

CEREAL_REGISTER_TYPE(GoOutOfQueueMessage);

#endif //UNEMPLOYED_MORRONS_GOOUTOFQUEUEMESSAGE_H
