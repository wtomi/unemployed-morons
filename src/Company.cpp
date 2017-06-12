//
// Created by tommy on 12.06.17.
//

#include "Company.h"

int Company::numberOfAgents;

Company::Company(int companyId, int maxDamageLevel, int maxNumberOfMorons)
        : maxNumberOfMorons(maxNumberOfMorons), companyId(companyId), maxDamageLevel(maxDamageLevel) {
    agentsRequests.assign(static_cast<unsigned long>(maxNumberOfMorons), nullptr);
}

Company::SharedPtr Company::Create(int companyId, int maxNumberOfMorons, int maxDamegeLevel, int numberOfAgents) {
    Company::numberOfAgents = numberOfAgents;
    return Company::SharedPtr(new Company(companyId, maxNumberOfMorons, maxNumberOfMorons));
}
