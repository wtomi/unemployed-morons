//
// Created by tommy on 10.06.17.
//

#define CATCH_CONFIG_MAIN
#include <catch/catch.hpp>
#include "../src/Monitor.h"
#include "../src/Message.h"
#include "../src/Serializer.h"
#include "../src/Messanger.h"

TEST_CASE("Sending and receiving packets", "[send]") {

    Monitor monitor;

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
        REQUIRE(aPackage.stringstreamMessage.str().compare(stringMessage) == 0);
    }
}

TEST_CASE("Message serializing and deserializing", "[serialize]") {
    Message message;
    message.clock = 5;
    message.word.assign("Hello");

    std::stringstream stringstream = Serializer::serialize(message);

    Message deserializedMessage;
    deserializedMessage = Serializer::deserialize(stringstream);

    REQUIRE(message.clock == deserializedMessage.clock);
    REQUIRE(message.word.compare(deserializedMessage.word) == 0);
}

TEST_CASE("Test Messendeg", "[messanger]") {
    Message message;
    message.clock = 5;
    message.word.assign("Hello");
    message.tag = 0;

    Messanger messanger;

    if(messanger.getRank() == 0) {
        for(int i = 1; i < messanger.getSize(); i++) {
            message.rank = i;
            messanger.send(message);
        }
    } else {
        Message receivedMessage = messanger.receive();
        REQUIRE(message.clock == receivedMessage.clock);
        REQUIRE(message.word.compare(receivedMessage.word) == 0);
    }
}