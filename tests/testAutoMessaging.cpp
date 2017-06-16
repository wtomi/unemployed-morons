//
// Created by tommy on 16.06.17.
//

#include <catch/catch.hpp>
#include "../src/Monitor.h"

TEST_CASE("Test automessaging") {
    const int TAG = 15;
    auto monitor = Monitor::getMonitor();
    std::string stringMsg("Hello!");
    auto stream = std::make_shared<std::stringstream>(stringMsg);
    auto packet = Packet::Create(stream, monitor->rank, TAG);
    monitor->send(packet);
    auto receivedPacket = monitor->receive(monitor->rank, TAG);
    CHECK(receivedPacket->stringstreamMessage->str().compare(stringMsg) == 0);
//    std::cout << "Received: " << receivedPacket->stringstreamMessage->str() << '\n';
}