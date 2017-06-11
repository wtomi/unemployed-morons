//
// Created by tommy on 11.06.17.
//

#include "Message.h"

Message::SharedPtr Message::Create() {
    return Message::SharedPtr(new Message);
}

void Message::sayWord() {
    std::cout<< "I am Message, my word: " << word << std::endl;
}
