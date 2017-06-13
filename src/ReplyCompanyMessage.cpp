//
// Created by tommy on 11.06.17.
//

#include "ReplyCompanyMessage.h"

ReplyCompanyMessage::SharedPtr ReplyCompanyMessage::Create(int receiver, int tag, int companyId, bool wantToEnter) {
    return ReplyCompanyMessage::SharedPtr(new ReplyCompanyMessage(receiver, tag, companyId, wantToEnter));
}

ReplyCompanyMessage::ReplyCompanyMessage(int rank, int tag, int companyId, bool wantToEnter) :
        Message(rank, tag, Message::Type::REPLY_COMPANY_REQUEST), companyId(companyId), wantToEnter(wantToEnter) {}
