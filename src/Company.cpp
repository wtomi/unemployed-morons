//
// Created by tommy on 12.06.17.
//

#include <cassert>
#include "Company.h"

int Company::numberOfAgents;

Company::Company(int companyId, int maxDamageLevel, int maxNumberOfMorons)
        : maxNumberOfMorons(maxNumberOfMorons), companyId(companyId), maxDamageLevel(maxDamageLevel) {
}

Company::SharedPtr Company::Create(int companyId, int maxNumberOfMorons, int maxDamegeLevel, int numberOfAgents) {
    Company::numberOfAgents = numberOfAgents;
    return Company::SharedPtr(new Company(companyId, maxDamegeLevel, maxNumberOfMorons));
}

int Company::getCompanyId() {
    return companyId;
}

void Company::addRequest(int agentId, long agentClock, int requestedPlaces) {
    //TODO implement
}
