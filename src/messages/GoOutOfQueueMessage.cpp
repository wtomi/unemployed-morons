//
// Created by tommy on 16.06.17.
//

#include "GoOutOfQueueMessage.h"

GoOutOfQueueMessage::SharedPtr GoOutOfQueueMessage::Create(int rank, int tag, int companyId, long requestClock) {
    return SharedPtr(new GoOutOfQueueMessage(rank, tag, companyId, requestClock));
}

GoOutOfQueueMessage::GoOutOfQueueMessage(int rank, int tag, int companyId, long requestClock) :
        Message(rank, tag, Message::Type::GO_OUT_OF_QUEUE), companyId(companyId), requestClock(requestClock) {
}
