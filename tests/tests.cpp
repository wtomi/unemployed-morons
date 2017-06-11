//
// Created by tommy on 10.06.17.
//

#define CATCH_CONFIG_MAIN
#include <catch/catch.hpp>
#include "../src/Monitor.h"
#include "../src/Message.h"
#include "../src/Serializer.h"
#include "../src/Messenger.h"

TEST_CASE("Sending and receiving packets", "[monitor]") {

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

TEST_CASE("Message serializing and deserializing", "[serializer]") {
    auto message = Message::Create();
    message->clock = 5;
    message->word.assign("Hello");

    std::stringstream stringstream = Serializer::serialize(message);

    auto deserializedMessage = Serializer::deserialize(stringstream);

    REQUIRE(message->clock == deserializedMessage->clock);
    REQUIRE(message->word.compare(deserializedMessage->word) == 0);
}

TEST_CASE("Test Messenger", "[messenger]") {
    auto message = Message::Create();
    message->clock = 5;
    message->word.assign("Hello");
    message->tag = 0;

    Messenger messenger;

    if(messenger.getRank() == 0) {
        for(int i = 1; i < messenger.getSize(); i++) {
            message->rank = i;
            messenger.send(message);
        }
    } else {
        auto receivedMessage = messenger.receive();
        REQUIRE(message->clock == receivedMessage->clock);
        REQUIRE(message->word.compare(receivedMessage->word) == 0);
    }
}