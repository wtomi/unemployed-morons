//
// Created by tommy on 11.06.17.
//

#include "ReplyCompanyMessage.h"

ReplyCompanyMessage::SharedPtr ReplyCompanyMessage::Create() {
    return ReplyCompanyMessage::SharedPtr(new ReplyCompanyMessage());
}
