//
// Created by tommy on 11.06.17.
//

#ifndef UNEMPLOYED_MORRONS_REPLYCOMPANYMESSAGE_H
#define UNEMPLOYED_MORRONS_REPLYCOMPANYMESSAGE_H

#include "Message.h"

class ReplyCompanyMessage : public Message {
public:
    typedef std::shared_ptr<ReplyCompanyMessage> SharedPtr;

    int companyId;
    bool wantToEnter;

    static SharedPtr Create(int receiver, int tag, int companyId, bool wantToEnter);

private:
    friend class cereal::access;
    ReplyCompanyMessage() : Message() {}
    ReplyCompanyMessage(int rank, int tag, int companyId, bool wantToEnter);

    template<class Archive>
    void serialize(Archive &ar) {
        ar(cereal::base_class<Message>(this), companyId, wantToEnter);
    }
};

CEREAL_REGISTER_TYPE(ReplyCompanyMessage);

#endif //UNEMPLOYED_MORRONS_REPLYCOMPANYMESSAGE_H
