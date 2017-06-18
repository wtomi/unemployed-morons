//
// Created by tommy on 18.06.17.
//

#ifndef UNEMPLOYED_MORRONS_REPLYBREAKCOMPANYMESSAGE_H
#define UNEMPLOYED_MORRONS_REPLYBREAKCOMPANYMESSAGE_H


#include "Message.h"

class ReplyBreakCompanyMessage : public Message {
public:
    typedef std::shared_ptr<ReplyBreakCompanyMessage> SharedPtr;

    int companyId;

    static SharedPtr Create(int rank, int tag, int companyId);

private:
    friend class cereal::access;
    ReplyBreakCompanyMessage(): Message() {}
    ReplyBreakCompanyMessage(int rank, int tag, int companyId);

    template<class Archive>
    void serialize(Archive &ar) {
        ar(cereal::base_class<Message>(this), companyId);
    }
};

CEREAL_REGISTER_TYPE(ReplyBreakCompanyMessage);

#endif //UNEMPLOYED_MORRONS_REPLYBREAKCOMPANYMESSAGE_H
