//
// Created by tommy on 18.06.17.
//

#include "RequestBreakCompanyMessage.h"

RequestBreakCompanyMessage::RequestBreakCompanyMessage(int rank, int tag, int companyId) :
        Message(rank, tag, Message::Type::REQUEST_BREAK_COMPANY), companyId(companyId) {

}
