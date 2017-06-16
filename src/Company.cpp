//
// Created by tommy on 12.06.17.
//

#include "Company.h"

Company::Company(int companyId, int maxDamageLevel, int maxNumberOfMorons)
        : maxNumberOfMorons(maxNumberOfMorons), companyId(companyId), maxDamageLevel(maxDamageLevel) {
}

Company::SharedPtr Company::Create(int companyId, int maxNumberOfMorons, int maxDamegeLevel) {
    return Company::SharedPtr(new Company(companyId, maxDamegeLevel, maxNumberOfMorons));
}

int Company::getCompanyId() {
    return companyId;
}

void Company::addRequest(int agentId, long agentClock, int requestedPlaces) {
    auto agentRequest = AgentRequest::Create(agentId, agentClock, requestedPlaces);
    requestsQueue.addRequest(agentRequest);
}

void Company::addReply() {
    numberOfReplies++;
}

int Company::getNumberOfReplies() {
    return numberOfReplies;
}
