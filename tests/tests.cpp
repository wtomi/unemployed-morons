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
#include "../src/RequestCompanyMessage.h"
#include "../src/ReplyCompanyMessage.h"

#define private public

#include "../src/Agent.h"

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
        CHECK(packet->stringstreamMessage->str().compare(stringMessage) == 0);
    }
}

TEST_CASE("Message serializing and deserializing", "[serializer]") {
    auto message = Message::Create();
    message->type = 5;
    message->tag = 5;

    auto stringstream = Serializer::serialize(message);

    auto deserializedMessage = Serializer::deserialize(stringstream);

    CHECK(message->type == deserializedMessage->type);
    CHECK(message->tag == message->tag);
}

TEST_CASE("Test Messenger", "[messenger]") {

    Messenger messenger;
    auto message = Message::Create();
    message->tag = 0;
    message->type = 1;

    SECTION("Simple send") {
        if (messenger.getRank() == 0) {
            for (int i = 1; i < messenger.getSize(); i++) {
                message->rank = i;
                messenger.send(message);
            }
        } else {
            auto receivedMessage = messenger.receiveFromAnySourceAnyTag();
            CHECK(message->tag == receivedMessage->tag);
            CHECK(message->type == receivedMessage->type);
        }
    }

    SECTION("Send to all") {
        messenger.sendToAll(message);
        int numberOtherProccesses = messenger.getSize() - 1;
        for (int i = 0; i < numberOtherProccesses; i++) {
            auto receivedMessage = messenger.receiveFromAnySourceAnyTag();
            CHECK(receivedMessage->rank != messenger.getRank());
            CHECK(message->tag == receivedMessage->tag);
            CHECK(message->type == receivedMessage->type);
        }
    }
}

TEST_CASE("Test passing derived messages", "[polymorphism]") {
    Messenger messenger;

    auto derivedMessage = DerivedMessage::Create();
    derivedMessage->tag = 0;
    derivedMessage->myword.assign("Hello");
    Message::SharedPtr message = derivedMessage;

    if (messenger.getRank() == 0) {
        for (int i = messenger.getRank(); i < messenger.getSize(); i++) {
            message->rank = i;
            messenger.send(message);
        }
    } else {
        Message::SharedPtr receivedMessage = messenger.receiveFromAnySourceAnyTag();

        CHECK(message->tag == receivedMessage->tag);
        auto derivedMessage = std::dynamic_pointer_cast<DerivedMessage>(message);
        auto receivedDerivedMessage = std::dynamic_pointer_cast<DerivedMessage>(receivedMessage);
        CHECK(derivedMessage->myword.compare(receivedDerivedMessage->myword) == 0);
    }
}

TEST_CASE("Test configuration and agent", "[configuration]") {
    auto configuration = Configuration::Create("config.json");
    int maxDamageLevels[] = {10, 15};
    int maxNumberOfMorons[] = {8, 12};
    auto &companies = configuration->companies;

    SECTION("Test configuration") {
        CHECK(configuration->initialMoronsNumberPerAgent == 10);
        for (int i = 0; i < companies.size(); i++) {
            CHECK(maxDamageLevels[i] == companies[i].maxDamageLevel);
            CHECK(maxNumberOfMorons[i] == companies[i].maxMorons);
        }
    }

    SECTION("Test company initializing in Agent") {
        Agent agent(configuration);
        for (int i = 0; i < companies.size(); i++) {
            CHECK(agent.companies[i]->maxDamageLevel == companies[i].maxDamageLevel);
            CHECK(agent.companies[i]->maxNumberOfMorons == companies[i].maxMorons);
        }
    }
}

TEST_CASE("Test request message", "[request]") {
    Messenger messenger;

    auto requestMessage = RequestCompanyMessage::Create();
    requestMessage->companyId = 10;
    requestMessage->requestedPlaces = 8;
    requestMessage->tag = 1;

    Message::SharedPtr message = requestMessage;

    if (messenger.getRank() == 0) {
        messenger.sendToAll(message);
    } else {
        Message::SharedPtr receivedMessage = messenger.receiveFromAnySourceAnyTag();
        CHECK(receivedMessage->tag == requestMessage->tag);
        auto receivedRequestMessage = std::dynamic_pointer_cast<RequestCompanyMessage>(receivedMessage);
        CHECK(receivedRequestMessage->companyId == requestMessage->companyId);
        CHECK(receivedRequestMessage->requestedPlaces == requestMessage->requestedPlaces);
    }
}

TEST_CASE("Test reply message", "[reply]") {
    Messenger messenger;

    auto replyMessage = ReplyCompanyMessage::Create();
    const int TAG = 2;
    replyMessage->tag = 2;
    replyMessage->wantToEnter = true;
    replyMessage->companyId = 9;

    Message::SharedPtr message = replyMessage;

    if (messenger.getRank() == 0) {
        messenger.sendToAll(message);
    } else {
        Message::SharedPtr receivedMessage = messenger.receiveFromAnySource(TAG);
        CHECK(receivedMessage->tag == replyMessage->tag);
        auto receivedReplyMessage = std::dynamic_pointer_cast<ReplyCompanyMessage>(receivedMessage);
        CHECK(receivedReplyMessage->companyId == replyMessage->companyId);
        CHECK(receivedReplyMessage->wantToEnter == replyMessage->wantToEnter);
    }
}

TEST_CASE("Test clock", "[clock]") {
    Messenger messenger;
    const int TAG = 3;
    auto message = Message::Create();
    message->tag = 3;


    SECTION("for sendToAll") {
        if (messenger.getRank() == 0) {
            messenger.sendToAll(message);
            messenger.sendToAll(message);
            CHECK(messenger.getClock() == 2);
        } else {
            auto receivedMessage = messenger.receiveFromAnySource(TAG);
            CHECK(receivedMessage->clock == 0);
            CHECK(messenger.getClock() == 1);
            receivedMessage = messenger.receiveFromAnySource(TAG);
            CHECK(receivedMessage->clock == 1);
            CHECK(messenger.getClock() == 2);
        }
    }

    SECTION("for send") {
        if (messenger.getRank() == 0) {
            message->rank = 1;
            messenger.send(message);
            message->rank = 2;
            messenger.send(message);
            CHECK(messenger.getClock() == 2);
        } else if (messenger.getRank() == 1) {
            auto receivedMessage = messenger.receiveFromAnySource(TAG);
            CHECK(receivedMessage->clock == 0);
            CHECK(messenger.getClock() == 1);
        } else if (messenger.getRank() == 2) {
            auto receivedMessaage = messenger.receiveFromAnySource(TAG);
            CHECK(receivedMessaage->clock == 1);
            CHECK(messenger.getClock() == 2);
        }
    }
}