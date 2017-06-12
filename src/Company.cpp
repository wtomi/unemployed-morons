//
// Created by tommy on 12.06.17.
//

#include "Company.h"

int Company::numberOfAgents = -1;

Company::Company(int companyId, int maxNumberOfMorons) : maxNumberOfMorons(maxNumberOfMorons), companyId(companyId) {
    for(int i = 0; i < numberOfAgents; i++) {
        agentsRequests.push_back(nullptr);
    }
}

Company::SharedPtr Company::Create(int companyId, int maxNumberOfMorons, int numberOfAgents) {
    Company::numberOfAgents = numberOfAgents;
    return Company::SharedPtr(new Company(companyId, maxNumberOfMorons));
}
