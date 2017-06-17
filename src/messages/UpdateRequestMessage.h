//
// Created by tommy on 17.06.17.
//

#ifndef UNEMPLOYED_MORRONS_UPDATEREQUESTMESSAGE_H
#define UNEMPLOYED_MORRONS_UPDATEREQUESTMESSAGE_H


#include "Message.h"

class UpdateRequestMessage : public Message {
public:
    typedef std::shared_ptr<UpdateRequestMessage> SharedPtr;

    int companyId;
    long requestClock;
    int updatedRequestedPlaces;

    static SharedPtr Create(int rank, int tag, int companyId, long requestClock, int updatedRequestedPlaces);

private:
    friend class cereal::access;

    UpdateRequestMessage() : Message() {}

    UpdateRequestMessage(int rank, int tag, int companyId, long requestClock, int updatedRequestsPlaces);

    template<class Archive>
    void serialize(Archive &ar) {
        ar(cereal::base_class<Message>(this), companyId, requestClock, updatedRequestedPlaces);
    }
};

CEREAL_REGISTER_TYPE(UpdateRequestMessage);

#endif //UNEMPLOYED_MORRONS_UPDATEREQUESTMESSAGE_H
