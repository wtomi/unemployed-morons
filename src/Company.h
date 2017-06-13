//
// Created by tommy on 12.06.17.
//

#ifndef UNEMPLOYED_MORRONS_COMPANY_H
#define UNEMPLOYED_MORRONS_COMPANY_H


#include <queue>
#include "AgentRequest.h"

class Company {
public:
    typedef std::shared_ptr<Company> SharedPtr;

    static SharedPtr Create(int companyId, int maxNumberOfMorons, int maxDamegeLevel, int numberOfAgents);

    int getCompanyId();
private:
    Company(int companyId, int maxDamageLevel, int maxNumberOfMorons);
    static int numberOfAgents;
    int companyId;
    int maxNumberOfMorons;
    int maxDamageLevel;
    std::priority_queue<AgentRequest::SharedPtr> agentsRquestQueue;
    std::vector<AgentRequest::SharedPtr> agentsRequests;
};


#endif //UNEMPLOYED_MORRONS_COMPANY_H
