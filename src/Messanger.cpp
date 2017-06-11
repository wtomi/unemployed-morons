//
// Created by tommy on 11.06.17.
//

#include "Messanger.h"
#include "Serializer.h"

void Messanger::send(Message message) {
    std::stringstream stringstreamMsg = Serializer::serialize(message);
    Packet packet(stringstreamMsg, message.rank, message.tag);
    monitor.send(packet);
}

Message Messanger::receive() {
    return receive(Monitor::ANY_SOURCE, Monitor::ANY_TAG);
}

Message Messanger::receive(int source, int tag) {
    Packet packet = monitor.receive(source, tag);
    Message message = Serializer::deserialize(packet.stringstreamMessage);
    message.rank = packet.rank;
    message.tag = packet.tag;
    return message;
}

int Messanger::getRank() {
    return monitor.rank;
}

int Messanger::getSize() {
    return monitor.size;
}
