//
// Created by tommy on 11.06.17.
//

#include "RequestCompanyMessage.h"

RequestCompanyMessage::SharedPtr RequestCompanyMessage::Create() {
    return RequestCompanyMessage::SharedPtr(new RequestCompanyMessage());
}
