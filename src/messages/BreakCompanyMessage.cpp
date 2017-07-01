//
// Created by tommy on 18.06.17.
//

#include "BreakCompanyMessage.h"

BreakCompanyMessage::SharedPtr BreakCompanyMessage::Create(int rank, int tag, int companyId, int breakCount) {
    return BreakCompanyMessage::SharedPtr(new BreakCompanyMessage(rank, tag, companyId, breakCount));
}

BreakCompanyMessage::BreakCompanyMessage(int rank, int tag, int companyId, int breakCount):
Message(rank, tag, Message::Type::BREAK_COMPANY), companyId(companyId), breakCount(breakCount) {

}
