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

int Company::getNumberOfFreePlacesForLastRequestOfCurrentAgent() {
    int occupiedPlaces = numberOfMoronsPlaced;
    for (auto agentRequest = requestsQueue.getFirstRequest();
         agentRequest != nullptr; agentRequest = requestsQueue.getNextRequest()) {
        if (agentRequest->agentId == lastRequest->agentId && agentRequest->requestClock == lastRequest->requestClock)
            break;
        occupiedPlaces += agentRequest->numberOfMorons;
    }
    int placesLeft = maxNumberOfMorons - occupiedPlaces;
    return (placesLeft >= 0) ? placesLeft : 0;
}

bool Company::isChangedLastRequestOfCurrentAgent() {
    if (lastRequest == nullptr) return false;
    auto request = requestsQueue.getAgentRequest(lastRequest->agentId, lastRequest->requestClock);
    assert(numberOfMoronsPlaced <= request->numberOfMorons);
    return numberOfMoronsPlaced != request->numberOfMorons;
}

void Company::placeMoronsInCompany(int numberOfMoronsPlaced) {
    this->numberOfMoronsPlaced += numberOfMoronsPlaced;
}

int Company::getNumberOfMoronsPlaced() {
    return numberOfMoronsPlaced;
}

void Company::updateLastRequestOfCurrentAgent() {
    updateRequest(lastRequest->agentId, lastRequest->requestClock, numberOfMoronsPlaced);
}

void Company::updateRequest(int agentId, long agentClock, int numberOfRequestedPlaces) {
    auto request = requestsQueue.getAgentRequest(agentId, agentClock);
    assert(request->numberOfMorons >= numberOfRequestedPlaces);
    request->numberOfMorons = numberOfRequestedPlaces;
}

void Company::removeRequest(int agentId, long agentClock) {
    requestsQueue.removeAgentRequest(agentId, agentClock);
}

void Company::removeLastRequestOfCurrentAgent() {
    assert(lastRequest != nullptr);
    requestsQueue.removeAgentRequest(lastRequest->agentId, lastRequest->requestClock);
    lastRequest = nullptr;
}

AgentRequest::SharedPtr Company::getLastRequestOfCurrentAgent() {
    assert(lastRequest != nullptr);
    return lastRequest;
}

bool Company::isUsed() {
    return numberOfMoronsPlaced != 0;
}


