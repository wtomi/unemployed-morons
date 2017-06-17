//
// Created by tommy on 12.06.17.
//

#include "Company.h"

Company::Company(int companyId, int maxDamageLevel, int maxNumberOfMorons, int agentId)
        : maxNumberOfMorons(maxNumberOfMorons), companyId(companyId),
          maxDamageLevel(maxDamageLevel), agentId(agentId) {
}

Company::SharedPtr Company::Create(int companyId, int maxNumberOfMorons, int maxDamegeLevel, int agentId) {
    return Company::SharedPtr(new Company(companyId, maxDamegeLevel, maxNumberOfMorons, agentId));
}

int Company::getCompanyId() {
    return companyId;
}

void Company::addRequestOfCurrentAgent(long agentClock, int requestedPlaces) {
    auto agentRequest = AgentRequest::Create(this->agentId, agentClock, requestedPlaces);
    lastRequest = agentRequest;
    requestsQueue.addRequest(agentRequest);
}

void Company::addRequest(int agentId, long agentClock, int requestedPlaces) {
    assert(agentId != this->agentId);
    auto agentRequest = AgentRequest::Create(agentId, agentClock, requestedPlaces);
    requestsQueue.addRequest(agentRequest);
}

void Company::addReply() {
    numberOfReplies++;
}

int Company::getNumberOfReplies() {
    return numberOfReplies;
}

int Company::getNumberOfFreePlacesForAgent(int agentId) {
    int occupiedPlaces = 0;
    for (auto agentRequest = requestsQueue.getFirstRequest();
         agentRequest != nullptr; agentRequest = requestsQueue.getNextRequest()) {
        if(agentRequest->agentId == agentId)
            break;
        occupiedPlaces += agentRequest->numberOfMorons;
    }
    int placesLeft = maxNumberOfMorons - occupiedPlaces;
    return (placesLeft >= 0) ? placesLeft : 0;
}

bool Company::isCahngedLastRequestOfCurrentAgent(int requestedPlaces) {
    auto request = requestsQueue.getAgentRequest(lastRequest->agentId, lastRequest->requestClock);
    assert(requestedPlaces <= request->numberOfMorons);
    return requestedPlaces != request->numberOfMorons;
}

void Company::placeMoronsInCompany(int numberOfMoronsPlaced) {
    this->numberOfMoronsPlaced = numberOfMoronsPlaced;
}

int Company::getNumberOfMoronsPlaced() {
    return numberOfMoronsPlaced;
}

void Company::updateRequest(int agentId, long agentClock, int numberOfRequestedPlaces) {
    auto request = requestsQueue.getAgentRequest(agentId, agentClock);
    assert(request->numberOfMorons <= numberOfRequestedPlaces);
    request->numberOfMorons = numberOfRequestedPlaces;
}

void Company::removeRequest(int agentId, long agentClock) {
    requestsQueue.removeAgentRequest(agentId, agentClock);
}

void Company::removeLastRequestOfCurrentAgent() {
    assert(lastRequest != nullptr);
    requestsQueue.removeAgentRequest(lastRequest->agentId, lastRequest->requestClock);
}

AgentRequest::SharedPtr Company::getLastRequestOfCurrentAgent() {
    assert(lastRequest != nullptr);
    return lastRequest;
}


