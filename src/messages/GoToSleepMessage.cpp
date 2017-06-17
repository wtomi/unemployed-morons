//
// Created by tommy on 18.06.17.
//

#include "GoToSleepMessage.h"

GoToSleepMessage::SharedPtr GoToSleepMessage::Create(int rank, int tag) {
    return GoToSleepMessage::SharedPtr(new GoToSleepMessage(rank, tag));
}

GoToSleepMessage::GoToSleepMessage(int rank, int tag) : Message(rank, tag, Message::Type::GO_TO_SLEEP) {

}
