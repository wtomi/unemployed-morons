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

    const int TAG = 1;
    std::string stringMessage("Hello!");
    auto stringStreamMessage = std::make_shared<std::stringstream>(stringMessage);
    if (monitor->rank == 0) {
        for (int i = 1; i < monitor->size; i++) {
            auto packet = Packet::Create(stringStreamMessage, i, TAG);
            monitor->send(packet);
        }
    } else {
        auto packet = monitor->receive(Monitor::ANY_SOURCE, TAG);
        CHECK(packet->stringstreamMessage->str().compare(stringMessage) == 0);
    }
}

TEST_CASE("Message serializing and deserializing", "[serializer]") {
    const int TYPE = 5;
    const int TAG = 2;
    auto message = Message::Create(-1, TYPE, TAG);
    message->clock = 12;

    auto stringstream = Serializer::serialize(message);

    auto deserializedMessage = Serializer::deserialize(stringstream);

    CHECK(message->type == deserializedMessage->type);
    CHECK(message->clock == deserializedMessage->clock);
}

TEST_CASE("Test Messenger", "[messenger]") {

    Messenger messenger;

    SECTION("Simple send") {
        const int TAG = 3;
        const int TYPE = 1;
        auto message = Message::Create(-1, TAG, TYPE);
        if (messenger.getRank() == 0) {
            for (int i = 1; i < messenger.getSize(); i++) {
                message->rank = i;
                messenger.send(message);
            }
        } else {
            auto receivedMessage = messenger.receiveFromAnySource(TAG);
            CHECK(message->tag == receivedMessage->tag);
            CHECK(message->type == receivedMessage->type);
        }
    }

    SECTION("Send to all") {
        const int TAG = 4;
        const int TYPE = 1;
        auto message = Message::Create(-1, TAG, TYPE);
        messenger.sendToAll(message);
        int numberOtherProccesses = messenger.getSize() - 1;
        for (int i = 0; i < numberOtherProccesses; i++) {
            auto receivedMessage = messenger.receiveFromAnySource(TAG);
            CHECK(receivedMessage->rank != messenger.getRank());
            CHECK(message->tag == receivedMessage->tag);
            CHECK(message->type == receivedMessage->type);
        }
    }
}

TEST_CASE("Test passing derived messages", "[polymorphism]") {
    Messenger messenger;

    auto derivedMessage = DerivedMessage::Create();
    const int TAG = 5;
    derivedMessage->tag = TAG;
    derivedMessage->myword.assign("Hello");
    Message::SharedPtr message = derivedMessage;

    if (messenger.getRank() == 0) {
        for (int i = messenger.getRank(); i < messenger.getSize(); i++) {
            message->rank = i;
            messenger.send(message);
        }
    } else {
        Message::SharedPtr receivedMessage = messenger.receiveFromAnySource(TAG);

        CHECK(message->tag == receivedMessage->tag);
        auto derivedMessage = std::dynamic_pointer_cast<DerivedMessage>(message);
        auto receivedDerivedMessage = std::dynamic_pointer_cast<DerivedMessage>(receivedMessage);
        CHECK(derivedMessage->myword.compare(receivedDerivedMessage->myword) == 0);
    }
}

TEST_CASE("Test configuration and agent", "[configuration]") {
    auto configuration = Configuration::Create("testconfig.json");
    int maxDamageLevels[] = {10, 15, 10};
    int maxNumberOfMorons[] = {8, 12, 8};
    auto &companies = configuration->companies;

    SECTION("Test configuration") {
        CHECK(configuration->initialMoronsNumberPerAgent == 10);
        for (int i = 0; i < companies.size(); i++) {
            CHECK(maxDamageLevels[i] == companies[i].maxDamageLevel);
            CHECK(maxNumberOfMorons[i] == companies[i].maxMorons);
        }
    }

    SECTION("Test Agent") {
        Agent agent(configuration);
        Messenger messenger;

        SECTION("Test company initializing in Agent") {
            for (int i = 0; i < companies.size(); i++) {
                CHECK(agent.companies[i]->maxDamageLevel == companies[i].maxDamageLevel);
                CHECK(agent.companies[i]->maxNumberOfMorons == companies[i].maxMorons);
            }
        }

        SECTION("Test request all companies") {
            agent.assignNewMorons();
            agent.requestEntranceToEveryCompany();
            for (int i = 0; i < messenger.getSize(); i++) {
                if (i != messenger.getRank()) {
                    for (int j = 0; j < agent.companies.size(); j++) {
                        auto receivedMessage = messenger.receive(i, Agent::TAG);
                        CHECK(receivedMessage->type == Message::Type::REQUEST_COMPANY);
                        CHECK(receivedMessage->tag == Agent::TAG);
                        auto receivedRequestMessage = std::dynamic_pointer_cast<RequestCompanyMessage>(receivedMessage);
                        CHECK(receivedRequestMessage->requestedPlaces == agent.numberOfMoronsLeft);
                    }
                }
            }
        }

        SECTION("Test single request all companies") {
            if (messenger.getRank() == 0) {
                agent.assignNewMorons();
                agent.requestEntranceToEveryCompany();
            } else {
                for (int j = 0; j < agent.companies.size(); j++) {
                    auto receivedMessage = messenger.receive(0, Agent::TAG);
                    CHECK(receivedMessage->type == Message::Type::REQUEST_COMPANY);
                    CHECK(receivedMessage->tag == Agent::TAG);
                    auto receivedRequestMessage = std::dynamic_pointer_cast<RequestCompanyMessage>(receivedMessage);
                    CHECK(receivedRequestMessage->requestedPlaces == agent.numberOfMoronsLeft);
                }
            }
        }

        SECTION("Test receive and handle message") {
            if(messenger.getRank() == 0) {
                agent.assignNewMorons();
                agent.requestEntranceToEveryCompany();
            } else {
                for(int i = 0; i < agent.companies.size(); i++) {
                    agent.receiveAndHandleMessage();
                }
            }
        }
    }
}

TEST_CASE("Test request message", "[request]") {
    Messenger messenger;

    const int TAG = 6;
    auto requestMessage = RequestCompanyMessage::Create(-1, TAG, 10, 8);

    Message::SharedPtr message = requestMessage;

    if (messenger.getRank() == 0) {
        messenger.sendToAll(message);
    } else {
        Message::SharedPtr receivedMessage = messenger.receiveFromAnySource(TAG);
        CHECK(receivedMessage->tag == requestMessage->tag);
        auto receivedRequestMessage = std::dynamic_pointer_cast<RequestCompanyMessage>(receivedMessage);
        CHECK(receivedRequestMessage->companyId == requestMessage->companyId);
        CHECK(receivedRequestMessage->requestedPlaces == requestMessage->requestedPlaces);
    }
}

TEST_CASE("Test reply message", "[reply]") {
    Messenger messenger;

    const int TAG = 7;
    auto replyMessage = ReplyCompanyMessage::Create(-1, TAG, 9);

    Message::SharedPtr message = replyMessage;

    if (messenger.getRank() == 0) {
        messenger.sendToAll(message);
    } else {
        Message::SharedPtr receivedMessage = messenger.receiveFromAnySource(TAG);
        CHECK(receivedMessage->tag == replyMessage->tag);
        auto receivedReplyMessage = std::dynamic_pointer_cast<ReplyCompanyMessage>(receivedMessage);
        CHECK(receivedReplyMessage->companyId == replyMessage->companyId);
    }
}

TEST_CASE("Test clock", "[clock]") {
    Messenger messenger;

    SECTION("for sendToAll") {
        const int TAG = 8;
        const int TYPE = 10;
        auto message = Message::Create(-1, TAG, TYPE);
        if (messenger.getRank() == 0) {
            messenger.sendToAll(message);
            messenger.sendToAll(message);
            CHECK(messenger.getClock() == 2);
        } else {
            auto receivedMessage = messenger.receiveFromAnySource(TAG);
            CHECK(receivedMessage->clock == 1);
            CHECK(messenger.getClock() == 2);
            receivedMessage = messenger.receiveFromAnySource(TAG);
            CHECK(receivedMessage->clock == 2);
            CHECK(messenger.getClock() == 3);
        }
    }

    SECTION("for send") {
        const int TAG = 9;
        const int TYPE = 10;
        auto message = Message::Create(-1, TAG, TYPE);
        if (messenger.getRank() == 0) {
            message->rank = 1;
            messenger.send(message);
            message->rank = 2;
            messenger.send(message);
            CHECK(messenger.getClock() == 2);
        } else if (messenger.getRank() == 1) {
            auto receivedMessage = messenger.receiveFromAnySource(TAG);
            CHECK(receivedMessage->clock == 1);
            CHECK(messenger.getClock() == 2);
        } else if (messenger.getRank() == 2) {
            auto receivedMessaage = messenger.receiveFromAnySource(TAG);
            CHECK(receivedMessaage->clock == 2);
            CHECK(messenger.getClock() == 3);
        }
    }
}