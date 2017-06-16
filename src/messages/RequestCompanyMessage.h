//
// Created by tommy on 11.06.17.
//

#ifndef UNEMPLOYED_MORRONS_REQUESTCOMPANYMESSAGE_H
#define UNEMPLOYED_MORRONS_REQUESTCOMPANYMESSAGE_H


#include "Message.h"

class RequestCompanyMessage : public Message {
public:
    typedef std::shared_ptr<RequestCompanyMessage> SharedPtr;

    int companyId;
    int requestedPlaces;

    static SharedPtr Create(int receiver, int tag, int companyId, int requestedPlaces);

private:
    friend class cereal::access;
    RequestCompanyMessage(): Message() {}
    RequestCompanyMessage(int receiver, int tag, int companyId, int requestedPlaces);

    template<class Archive>
    void serialize(Archive &ar) {
        ar(cereal::base_class<Message>(this), companyId, requestedPlaces);
    }
};

CEREAL_REGISTER_TYPE(RequestCompanyMessage);

#endif //UNEMPLOYED_MORRONS_REQUESTCOMPANYMESSAGE_H
