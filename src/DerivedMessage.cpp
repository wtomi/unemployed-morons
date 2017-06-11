//
// Created by tommy on 11.06.17.
//

#include "DerivedMessage.h"

void DerivedMessage::sayWord() {
    std::cout << "I'm DerivedMessage, word: " << word << " and only my word: " << myword << std::endl;
}

DerivedMessage::SharedPtr DerivedMessage::Create() {
    return DerivedMessage::SharedPtr(new DerivedMessage());
}
