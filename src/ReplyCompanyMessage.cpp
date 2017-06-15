//
// Created by tommy on 11.06.17.
//

#include "ReplyCompanyMessage.h"

ReplyCompanyMessage::SharedPtr ReplyCompanyMessage::Create(int receiver, int tag, int companyId) {
    return ReplyCompanyMessage::SharedPtr(new ReplyCompanyMessage(receiver, tag, companyId));
}

ReplyCompanyMessage::ReplyCompanyMessage(int rank, int tag, int companyId) :
        Message(rank, tag, Message::Type::REPLY_COMPANY_REQUEST), companyId(companyId) {}
