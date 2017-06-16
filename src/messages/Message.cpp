//
// Created by tommy on 11.06.17.
//

#include "Message.h"

Message::SharedPtr Message::Create(int rank, int tag, int type) {
    return Message::SharedPtr(new Message(rank, tag, type));
}

Message::Message(int rank, int tag, int type) : type(type), rank(rank), tag(tag) {

}
