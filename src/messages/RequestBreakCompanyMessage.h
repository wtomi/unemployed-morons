//
// Created by tommy on 18.06.17.
//

#ifndef UNEMPLOYED_MORRONS_REQUESTBREAKCOMPANYMESSAGE_H
#define UNEMPLOYED_MORRONS_REQUESTBREAKCOMPANYMESSAGE_H

#include "Message.h"

class RequestBreakCompanyMessage : public Message {
public:
    typedef std::shared_ptr<RequestBreakCompanyMessage> SharedPtr;

    int companyId;

    static SharedPtr Create(int rank, int tag, int companyId);

private:
    friend class cereal::access;
    RequestBreakCompanyMessage(): Message() {}
    RequestBreakCompanyMessage(int rank, int tag, int companyId);

    template<class Archive>
    void serialize(Archive &ar) {
        ar(cereal::base_class<RequestBreakCompanyMessage>(this), companyId);
    }
};

CEREAL_REGISTER_TYPE(RequestBreakCompanyMessage);

#endif //UNEMPLOYED_MORRONS_REQUESTBREAKCOMPANYMESSAGE_H
