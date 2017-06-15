//
// Created by tommy on 15.06.17.
//

#include <catch/catch.hpp>
#include <climits>
#include <iostream>
#include "../src/RequestsQueue.h"

void printRequest(AgentRequest::SharedPtr &request);

TEST_CASE("Test Requests Queue") {
    RequestsQueue requestsQueue;
    const int NUMBER_OF_REQUESTS = 10;
    const int clocks[] = {5, 4, 3, 0, 5, 8, 7, 1, 5, 2};
    const int numberOfMorons[] = {1, 5, 65, 9, 7, 4, 4, 2, 3, 41};
    for (int i = NUMBER_OF_REQUESTS-1; i >= 0; i--) {
        auto request = AgentRequest::Create(i, clocks[i], numberOfMorons[i]);
        requestsQueue.addRequest(request);
    }

    SECTION("Test get AgentRequest") {
        const int AGENT_ID = 5;
        auto request = requestsQueue.getAgentRequest(AGENT_ID);
        CHECK(request->clock == clocks[AGENT_ID]);
        CHECK(request->numberOfMorons == numberOfMorons[AGENT_ID]);
        CHECK(request->agentId == AGENT_ID);
    }

    SECTION("Test getNextRequest") {
        long lastClock = LONG_MIN;
        for (auto request = requestsQueue.getFirstRequest();
             request != nullptr; request = requestsQueue.getNextRequest()) {
            CHECK(request->clock >= lastClock);
            lastClock = request->clock;
//            printRequest(request);
        }
    }
}

void printRequest(AgentRequest::SharedPtr &request) {
    const int W = 3;
    std::cout << "Agent id:" << std::setw(W) << request->agentId
              << " | clock: " << std::setw(W) << request->clock
              << " | morons: " << std::setw(W) << request->numberOfMorons
              << "\n";
}