//
// Created by tommy on 10.06.17.
//

#define CATCH_CONFIG_MAIN
#include <catch/catch.hpp>
#include "../src/Monitor.h"

TEST_CASE("Sending and receiving packets", "[send, receive, packet]") {

    Monitor monitor(nullptr, nullptr);

    const int TAG = 0;
    std::string stringMessage("Hello!");
    std::stringstream stringStreamMessage(stringMessage);
    if(monitor.rank == 0) {
        for(int i = 1; i < monitor.size; i++) {
            Packet package(stringStreamMessage, i, TAG);
            monitor.send(package);
        }
    } else {
        Packet aPackage = monitor.receive();
        std::cout << aPackage.stringstreamMessage.str() << "\n";
        REQUIRE(aPackage.stringstreamMessage.str().compare(stringMessage) == 0);
    }
}