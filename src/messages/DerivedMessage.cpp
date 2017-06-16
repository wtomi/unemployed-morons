//
// Created by tommy on 11.06.17.
//

#include "DerivedMessage.h"

DerivedMessage::SharedPtr DerivedMessage::Create() {
    return DerivedMessage::SharedPtr(new DerivedMessage());
}
