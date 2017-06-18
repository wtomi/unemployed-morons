//
// Created by tommy on 18.06.17.
//

#include "BreakCompanyMessage.h"

BreakCompanyMessage::SharedPtr BreakCompanyMessage::Create(int rank, int tag, int companyId) {
    return BreakCompanyMessage::SharedPtr(new BreakCompanyMessage(rank, tag, companyId));
}

BreakCompanyMessage::BreakCompanyMessage(int rank, int tag, int companyId) :
        Message(rank, tag, Message::Type::BREAK_COMPANY), companyId(companyId) {

}
