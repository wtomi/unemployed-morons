//
// Created by tommy on 11.06.17.
//

#include "Configuration.h"
#include "Monitor.h"

const int Configuration::TAG = 0;

Configuration::SharedPtr Configuration::Create(std::string filepath) {
    std::ifstream inputStream(filepath);
    return Configuration::SharedPtr(new Configuration(inputStream));
}

Configuration::SharedPtr Configuration::CreateFromReceivedMessage() {
    auto monitor = Monitor::getMonitor();
    auto packet = monitor->receive(Monitor::ANY_SOURCE, TAG);
    return Configuration::SharedPtr(new Configuration(*(packet->stringstreamMessage.get())));
}

Configuration::Configuration(std::istream &stream) {
    cereal::JSONInputArchive inputArchive(stream);
    inputArchive(*this);
}

void Configuration::sendConfigurationToAllProceses() {
    auto monitor = Monitor::getMonitor();
    auto streamMessage = std::make_shared<std::stringstream>();
    {
        cereal::JSONOutputArchive outputArchive(*(streamMessage.get()));
        outputArchive(*this);
    }
    auto packet = Packet::Create(streamMessage, -1, TAG);
    sendToAll(monitor, packet);
}

void Configuration::sendToAll(Monitor::SharedPtr monitor, Packet::SharedPtr packet) {
    for (int i = 0; i < monitor->size; i++) {
        if (i != monitor->rank) {
            packet->rank = i;
            monitor->send(packet);
        }
    }
}
