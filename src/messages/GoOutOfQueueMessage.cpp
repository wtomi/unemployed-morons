//
// Created by tommy on 16.06.17.
//

#include "GoOutOfQueueMessage.h"

GoOutOfQueueMessage::SharedPtr GoOutOfQueueMessage::Create(int rank, int tag, int companyId) {
    return SharedPtr(new GoOutOfQueueMessage(rank, tag, companyId));
}

GoOutOfQueueMessage::GoOutOfQueueMessage(int rank, int tag, int companyId) :
        Message(rank, tag, Message::Type::GO_OUT_OF_QUEUE) {
    this->companyId = companyId;
}
