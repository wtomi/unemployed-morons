//
// Created by tommy on 18.06.17.
//

#include "ReplyBreakCompanyMessage.h"

ReplyBreakCompanyMessage::ReplyBreakCompanyMessage(int rank, int tag, int companyId) :
        Message(rank, tag, Message::Type::REPLY_BREAK_COMPANY), companyId(companyId) {
}

ReplyBreakCompanyMessage::SharedPtr ReplyBreakCompanyMessage::Create(int rank, int tag, int companyId) {
    return ReplyBreakCompanyMessage::SharedPtr(new ReplyBreakCompanyMessage(rank, tag, companyId));
}
