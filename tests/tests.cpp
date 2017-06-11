//
// Created by tommy on 10.06.17.
//

#define CATCH_CONFIG_MAIN

#include <catch/catch.hpp>
#include "../src/Monitor.h"
#include "../src/Message.h"
#include "../src/Serializer.h"
#include "../src/Messenger.h"
#include "../src/DerivedMessage.h"
#include "../src/Configuration.h"

TEST_CASE("Sending and receiving packets", "[monitor]") {

    auto monitor = Monitor::getMonitor();

    const int TAG = 0;
    std::string stringMessage("Hello!");
    auto stringStreamMessage = std::make_shared<std::stringstream>(stringMessage);
    if (monitor->rank == 0) {
        for (int i = 1; i < monitor->size; i++) {
            auto packet = Packet::Create(stringStreamMessage, i, TAG);
            monitor->send(packet);
        }
    } else {
        auto packet = monitor->receive();
        REQUIRE(packet->stringstreamMessage->str().compare(stringMessage) == 0);
    }
}

TEST_CASE("Message serializing and deserializing", "[serializer]") {
    auto message = Message::Create();
    message->clock = 5;

    auto stringstream = Serializer::serialize(message);

    auto deserializedMessage = Serializer::deserialize(stringstream);

    REQUIRE(message->clock == deserializedMessage->clock);
}

TEST_CASE("Test Messenger", "[messenger]") {

    Messenger messenger;
    auto message = Message::Create();
    message->clock = 5;
    message->tag = 0;

    SECTION("Simple send") {
        if (messenger.getRank() == 0) {
            for (int i = 1; i < messenger.getSize(); i++) {
                message->rank = i;
                messenger.send(message);
            }
        } else {
            auto receivedMessage = messenger.receive();
            REQUIRE(message->clock == receivedMessage->clock);
            REQUIRE(message->tag == receivedMessage->tag);
        }
    }

    SECTION("Send to all") {
        messenger.sendToAll(message);
        int numberOtherProccesses = messenger.getSize() - 1;
        for (int i = 0; i < numberOtherProccesses; i++) {
            auto receivedMessage = messenger.receive();
            REQUIRE(receivedMessage->rank != messenger.getRank());
            REQUIRE(message->clock == receivedMessage->clock);
            REQUIRE(message->tag == receivedMessage->tag);
        }
    }
}

TEST_CASE("Test passing derived messages", "[polymorphism]") {
    Messenger messenger;

    auto derivedMessage = DerivedMessage::Create();
    derivedMessage->clock = 10;
    derivedMessage->tag = 0;
    Message::SharedPtr message = derivedMessage;

    if (messenger.getRank() == 0) {
        for (int i = messenger.getRank(); i < messenger.getSize(); i++) {
            message->rank = i;
            messenger.send(message);
        }
    } else {
        Message::SharedPtr receivedMessage = messenger.receive();

        REQUIRE(message->clock == receivedMessage->clock);
        REQUIRE(message->tag == receivedMessage->tag);
        auto derivedMessage = std::static_pointer_cast<DerivedMessage>(message);
        auto receivedDerivedMessage = std::static_pointer_cast<DerivedMessage>(receivedMessage);
    }
}

TEST_CASE("Test configuration", "[configuration]") {
    Configuration configuration("config.json");
    int maxDamageLevels[] = {10, 15};
    int maxNumberOfMorons[] = {8, 12};
    REQUIRE(configuration.initialMoronsNumberPerAgent == 10);
    auto &companies = configuration.companies;
    for (int i = 0; i < companies.size(); i++) {
        REQUIRE(maxDamageLevels[i] == companies[i].maxDamageLevel);
        REQUIRE(maxNumberOfMorons[i] == companies[i].maxMorons);
    }
}