//
// Created by tommy on 18.06.17.
//

#include "WakeUpMessage.h"

WakeUpMessage::SharedPtr WakeUpMessage::Create(int rank, int tag) {
    return WakeUpMessage::SharedPtr(new WakeUpMessage(rank, tag));
}

WakeUpMessage::WakeUpMessage(int rank, int tag): Message(rank, tag, Message::Type::WAKE_UP) {

}
