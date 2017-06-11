//
// Created by tommy on 11.06.17.
//

#include "Message.h"

Message::SharedPtr Message::Create() {
    return Message::SharedPtr(new Message);
}
