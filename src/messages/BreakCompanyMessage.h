//
// Created by tommy on 18.06.17.
//

#ifndef UNEMPLOYED_MORRONS_BREAKCOMPANYMESSAGE_H
#define UNEMPLOYED_MORRONS_BREAKCOMPANYMESSAGE_H


#include "Message.h"

class BreakCompanyMessage : public Message {
public:
    typedef std::shared_ptr<BreakCompanyMessage> SharedPtr;

    int companyId;
    int breakCount;

    static SharedPtr Create(int rank, int tag, int companyId, int breakCount);

private:
    friend class cereal::access;

    BreakCompanyMessage() : Message() {}

    BreakCompanyMessage(int rank, int tag, int companyId, int breakCount);

    template<class Archive>
    void serialize(Archive &ar) {
        ar(cereal::base_class<Message>(this), companyId, breakCount);
    }
};

CEREAL_REGISTER_TYPE(BreakCompanyMessage);

#endif //UNEMPLOYED_MORRONS_BREAKCOMPANYMESSAGE_H
