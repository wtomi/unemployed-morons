//
// Created by tommy on 17.06.17.
//

#include "UpdateRequestMessage.h"

UpdateRequestMessage::SharedPtr
UpdateRequestMessage::Create(int rank, int tag, int companyId, long requestClock, int updatedRequestedPlaces) {
    return UpdateRequestMessage::SharedPtr(
            new UpdateRequestMessage(rank, tag, companyId, requestClock, updatedRequestedPlaces));
}

UpdateRequestMessage::UpdateRequestMessage(int rank, int tag, int companyId, long requestClock,
                                           int updatedRequestsPlaces) :
        Message(rank, tag, Message::Type::UPDATE_REQUEST),
        companyId(companyId), requestClock(requestClock), updatedRequestedPlaces(updatedRequestsPlaces) {
}
