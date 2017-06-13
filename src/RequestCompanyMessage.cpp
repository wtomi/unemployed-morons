//
// Created by tommy on 11.06.17.
//

#include "RequestCompanyMessage.h"

RequestCompanyMessage::SharedPtr
RequestCompanyMessage::Create(int receiver, int tag, int companyId, int requestedPlaces) {
    return RequestCompanyMessage::SharedPtr(new RequestCompanyMessage(receiver, tag, companyId, requestedPlaces));
}

RequestCompanyMessage::RequestCompanyMessage(int receiver, int tag, int companyId, int requestedPlaces)
        : Message(receiver, tag, Message::Type::REQUEST_COMPANY), companyId(companyId),
          requestedPlaces(requestedPlaces) {}
