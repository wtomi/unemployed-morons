//
// Created by tommy on 11.06.17.
//

#include "Messenger.h"
#include "Serializer.h"

void Messenger::sendToAll(Message::SharedPtr &message) {
    message->clock = clock;
    for (int i = 0; i < getSize(); i++) {
        if (i != getRank()) {
            message->rank = i;
            sendMessage(message);
        }
    }
    clock++;
}

void Messenger::send(Message::SharedPtr &message) {
    message->clock = clock;
    sendMessage(message);
    clock++;
}

void Messenger::sendMessage(const Message::SharedPtr &message) const {
    auto stringstreamMsg = Serializer::serialize(message);
    auto packet = Packet::Create(stringstreamMsg, message->rank, message->tag);
    monitor->send(packet);
}

Message::SharedPtr Messenger::receiveFromAnySourceAnyTag() {
    return receive(Monitor::ANY_SOURCE, Monitor::ANY_TAG);
}

Message::SharedPtr Messenger::receiveFromAnySource(int tag) {
    return receive(Monitor::ANY_SOURCE, tag);
}

Message::SharedPtr Messenger::receive(int source, int tag) {
    auto packet = monitor->receive(source, tag);
    auto message = Serializer::deserialize(packet->stringstreamMessage);
    message->rank = packet->rank;
    message->tag = packet->tag;

    if(message->clock > clock) {
        clock = message->clock;
    }
    clock++;

    return message;
}

int Messenger::getRank() {
    return monitor->rank;
}

int Messenger::getSize() {
    return monitor->size;
}

long Messenger::getClock() {
    return clock;
}
